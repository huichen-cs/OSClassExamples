package edu.cuny.brooklyn.ioaio.controller;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

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
	private final static int BUF_SIZE = 1 << 4; //TODO: experiment with buffer size

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
	
	private DoubleProperty progressProperty;
	
	public void initialize() {
		LOGGER.info(getClass().getSimpleName() + " is initializing.");
		fileChooser = new FileChooser();
		copyFromButton.setOnAction(e -> selectSourceFile());
		copyToButton.setOnAction(e -> selectDestinationFile());
		copyButton.setOnAction(e -> copyFile());
		resetUIForNextCopy();
		progressProperty = new SimpleDoubleProperty(0f);
		copyingProgress.progressProperty().bind(progressProperty);
	}

	public void setStage(Stage stage) {
		if (stage == null) {
			throw new IllegalArgumentException("Stage must not be null.");
		}
		this.stage = stage;
	}
	

	/*
	 * You may implement this using I/O stream since we demonstrate synchronous blocking I/O
	 */
	private void copyFile() {
		
		try (FileChannel inChannel = FileChannel.open(srcFilePath, StandardOpenOption.READ);
			FileChannel outChannel = FileChannel.open(dstFilePath, StandardOpenOption.CREATE_NEW, StandardOpenOption.WRITE)) {
			
			// channle's transferTo method can do copy in one step, but
			// the following demo's the read & write & buffer uses
			copyingInfoLabel.setText("Copying to " + dstFilePath.toString());
			ByteBuffer byteBuffer = ByteBuffer.allocate(BUF_SIZE);
			setUIForCopyInProgress(outChannel);
			long fileSize = inChannel.size();
			long bytesWritten = 0;
			progressProperty.set(0f);
			while (inChannel.read(byteBuffer) > 0) {
				// Buffer: flip between "write into the buffer", and "read from the buffer"
				byteBuffer.flip();
				int numBytes = outChannel.write(byteBuffer);
				if (numBytes >= 0) {
					bytesWritten += numBytes;
				}
				// Buffer: clear the buffer for the next "read into buffer" operation
				byteBuffer.clear();
				progressProperty.set((double)bytesWritten / (double)fileSize);
			}
			copyingInfoLabel.setText("Copying completed.");
			resetUIForNextCopy();
		} catch (IOException e) {
			LOGGER.error(e.getMessage(), e);
			// TODO: add notification: copy failed
		} 
	}
	
	private void cancelCopyFile(FileChannel channel) {
		try {
			if (channel.isOpen()) {
				channel.close();
			}
		} catch (IOException e) {
			LOGGER.error(e.getMessage(), e);
			// TODO: add notification: cancel may not be successful
		}
	}
	
	
	private void enableCopyButtonIf() {
		if (srcFilePath != null && dstFilePath != null) {
			copyButton.setDisable(false);
		}
	}
	
	private void resetUIForNextCopy() {
		copyFromField.setDisable(true);
		copyToField.setDisable(true);
		copyButton.setDisable(true);
		cancelButton.setDisable(true);
		copyFromField.setText("");
		copyToField.setText("");
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
	
	private void setUIForCopyInProgress(FileChannel channel) {
		copyButton.setDisable(true);
		cancelButton.setDisable(false);
		cancelButton.setOnAction(e -> cancelCopyFile(channel));
	}
	
	private void validateStage() {
		if (stage == null) {
			throw new IllegalStateException("Stage must not be null.");
		}
	}

}
