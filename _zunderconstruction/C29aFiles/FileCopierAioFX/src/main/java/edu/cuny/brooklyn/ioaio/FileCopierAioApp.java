package edu.cuny.brooklyn.ioaio;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.cuny.brooklyn.ioaio.controller.MainViewController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * Hello world!!
 *
 * In Eclipse IDE, suggest to install the e(fx)clilpse plugin
 */
public class FileCopierAioApp extends Application {
	private final static Logger LOGGER = LoggerFactory.getLogger(FileCopierAioApp.class);
	private final static String MAIN_VIEW_FXML = "view/fxml_mainview.fxml";
	private final static String APP_TITLE = "File Copier using asynchronous non-blocking I/O";
	
	public static void main(String[] args) {
		launch(args);
	}
	
	@Override
	public void init() {
		LOGGER.info("Launching the app ...");		
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		FXMLLoader fxmlLoader = new FXMLLoader();
		Parent mainView = fxmlLoader.load(getClass().getResourceAsStream(MAIN_VIEW_FXML));
		MainViewController controller = fxmlLoader.getController();
		controller.setStage(primaryStage);
		
		Scene scene = new Scene(mainView);
		primaryStage.setScene(scene);
		primaryStage.setTitle(APP_TITLE);
		primaryStage.show();
	}
	
	@Override
	public void stop() {
		LOGGER.info("Exiting the app...");
	}
}
