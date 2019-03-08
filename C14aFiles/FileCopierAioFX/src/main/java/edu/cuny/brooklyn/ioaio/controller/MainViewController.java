package edu.cuny.brooklyn.ioaio.controller;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousFileChannel;
import java.nio.channels.CompletionHandler;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javafx.application.Platform;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class MainViewController {
	private final static Logger LOGGER = LoggerFactory.getLogger(MainViewController.class);
	/* TODO: experiment with buffer size, such as, 1 << 4, 1 << 10, 1 << 20
	 *		 the smaller the buffer is, the chance of race condition increases if not designed
	 *		 well.
	 */
	private final static int BUF_SIZE = 1 << 10; 

	@FXML
	private Button copyFromButton;

	@FXML
	private Button copyToButton;
	
	@FXML
	private TextField copyFromField;
	
	@FXML
	private TextField copyToField;

	@FXML
	private ProgressBar copyingProgress;

	@FXML
	private Button cancelButton;
	
	@FXML
	private Button copyButton;
	
	@FXML
	private Label copyingInfoLabel;
	
	private Stage stage;

	private FileChooser fileChooser;
	
	private Path srcFilePath;
	private Path dstFilePath;
	
	private AsynchronousFileChannel inChannel;
	private AsynchronousFileChannel outChannel;
	private long fileSize;
	private long filePosition;
	private ReadCompletionHandler inHandler;
	private WriteCompletionHandler outHandler;
	private DoubleProperty progressProperty;
	/*
	 * Design Consideration:
	 * 	Using a shared buffer between channel read and channel write may lead to a race condition.
	 */
	
	
	/* There doesn't seem to have a reliable method to cancel a read/write in progress. 
	 * We run this close method mutual exclusively with read & write; otherwise, channels
	 * can be closed when doing read & write. 
	 * 
	 * In Java, the simplest approach perhaps is to use the monitor provided by Java as 
	 * shown below. */
	public void close() {
		try {
			synchronized (this) {
				if (inChannel != null) {
					inChannel.close();
					inChannel = null;
				}

				if (outChannel != null) {
					outChannel.close();
					outChannel = null;
				}
			}
			progressProperty.set(0f);
			copyingInfoLabel.setText("Copying canceled");
			if (dstFilePath != null && Files.exists(dstFilePath)) {
				Files.delete(dstFilePath);
			}
		} catch (IOException e) {
			LOGGER.error("Cannot close channels.", e);
			// TODO: notify users. may quit.
		}
	}
	
	public void initialize() {
		LOGGER.info(getClass().getSimpleName() + " is initializing.");
		
		fileChooser = new FileChooser();
		copyFromButton.setOnAction(e -> selectSourceFile());
		copyToButton.setOnAction(e -> selectDestinationFile());
		copyButton.setOnAction(e -> copyFile());
		cancelButton.setOnAction(e -> cancelCopyFile());
		
		initUI();
		
		progressProperty = new SimpleDoubleProperty(0f);
		copyingProgress.progressProperty().bind(progressProperty);
		inHandler = new ReadCompletionHandler();
		outHandler = new WriteCompletionHandler();
	}
	

	public void setStage(Stage stage) {
		if (stage == null) {
			throw new IllegalArgumentException("Stage must not be null.");
		}
		this.stage = stage;
	}

	
	
	private void initUI() {
		copyFromField.setDisable(true);
		copyToField.setDisable(true);
		copyButton.setDisable(true);
		cancelButton.setDisable(true);
		copyFromField.setText("");
		copyToField.setText("");
	}
	
	/*
	 * You may implement this using I/O stream since we demonstrate synchronous blocking I/O
	 */
	private void copyFile() {
		LOGGER.debug("entered copyFile() ...");
		try {
			startAioCopyFile();
		} catch (IOException e) {
			// TODO;
		} finally {
			// TODO
		}
	}

	private void cancelCopyFile() {
		close();
	}
	
	
	private void enableCopyButtonIf() {
		if (srcFilePath != null && dstFilePath != null) {
			copyButton.setDisable(false);
		}
	}

	
	private void selectDestinationFile() {
		validateStage();
		fileChooser.setTitle("Select a file to copy to");
		File file = fileChooser.showSaveDialog(stage);
		dstFilePath = file != null ? file.toPath() : null;		
		if (dstFilePath != null) {
			copyToField.setText(dstFilePath.toString());
		}
		enableCopyButtonIf();
		progressProperty.set(0f);
	}

	private void selectSourceFile() {
		validateStage();
		fileChooser.setTitle("Select a file to copy from");
		File file = fileChooser.showOpenDialog(stage);
		srcFilePath = file != null ? file.toPath() : null;
		if (srcFilePath != null) {
			copyFromField.setText(srcFilePath.toString());
		}
		enableCopyButtonIf();
		progressProperty.set(0f);
	}
	
	private void setUIForCopyInProgress() {
		copyButton.setDisable(true);
		cancelButton.setDisable(false);
	}
	
	private void setUIForNextCopy(String msg) {
		copyingInfoLabel.setText(msg);
		initUI();	
	}
	
	
	private void startAioCopyFile() throws IOException {
		LOGGER.debug("Entered startAioCopyFile.");
		inChannel = AsynchronousFileChannel.open(srcFilePath, StandardOpenOption.READ);
		outChannel = AsynchronousFileChannel.open(dstFilePath, StandardOpenOption.CREATE_NEW, StandardOpenOption.WRITE);
			
		fileSize = inChannel.size();
		filePosition = 0;
		progressProperty.set(0f);
		copyingInfoLabel.setText("Copying to " + dstFilePath.toString());
		setUIForCopyInProgress();

		ByteBuffer byteBuffer = ByteBuffer.allocate(BUF_SIZE);
		synchronized (this) {
			if (inChannel != null && inChannel.isOpen()) inChannel.read(byteBuffer, filePosition, byteBuffer, inHandler);
		}
	}
	
	private void validateStage() {
		if (stage == null) {
			throw new IllegalStateException("Stage must not be null.");
		}
	}

	private class ReadCompletionHandler implements CompletionHandler<Integer, ByteBuffer> {

		@Override
		public void completed(Integer result, ByteBuffer byteBufferRead) {
			// TODO Auto-generated method stub
			LOGGER.debug("Bytes read: " + result.intValue());
			if (result.intValue() <= 0) {
				LOGGER.error("read passed the end of file.");
				throw new IllegalStateException("Logical error: read passed the end of the file");
			}

			byteBufferRead.flip();
			synchronized (this) {
				if (outChannel != null && outChannel.isOpen()) outChannel.write(byteBufferRead, filePosition, new Long(filePosition), outHandler);
			}
			
			if (filePosition + result.intValue() < fileSize) {
				LOGGER.debug("Read again at " + filePosition);
				ByteBuffer byteBufferToRead = ByteBuffer.allocate(BUF_SIZE);
				synchronized (this) {
					if (inChannel != null && inChannel.isOpen()) inChannel.read(byteBufferToRead, filePosition + result.intValue(), byteBufferToRead, inHandler);
				}
			}
		}

		@Override
		public void failed(Throwable e, ByteBuffer attachment) {
			// TODO: deal with the error
			LOGGER.error("Failed to read the file", e);
		}
	}
	
	private class WriteCompletionHandler implements CompletionHandler<Integer, Long> {
		
		@Override
		public void completed(Integer result, Long attachment) {
			LOGGER.debug("Wrote " + result + " bytes");
			filePosition = attachment.longValue() + result.intValue();
			progressProperty.set((double)filePosition/(double)fileSize);
			LOGGER.debug("Total bytes written: " + filePosition);
			
			
			if (filePosition == fileSize) {
				Platform.runLater(() -> setUIForNextCopy("Copy compled"));
				close();
			} else if (filePosition > fileSize) {
				Platform.runLater(() -> setUIForNextCopy("Inconsistent copy, should never happen"));
				close();
				throw new IllegalStateException("File copy ecountered a logical error.");
			}
		}

		@Override
		public void failed(Throwable e, Long attachment) {
			// TODO: deal with error
			LOGGER.error("Write failure.", e);
		}
		
	}
}
