package edu.cuny.brooklyn.ioaio;

import edu.cuny.brooklyn.ioaio.controller.MainViewController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Hello world!!
 *
 * <p>In Eclipse IDE, suggest to install the e(fx)clilpse plugin
 */
public final class FileCopierAioApp extends Application {
  private static final Logger LOGGER = LoggerFactory.getLogger(FileCopierAioApp.class);
  private static final String MAIN_VIEW_FXML = "view/fxml_mainview.fxml";
  private static final String APP_TITLE = "File Copier using asynchronous non-blocking I/O";

  public static void main(final String[] args) {
    launch(args);
  }

  @Override
  public void init() {
    LOGGER.info("Launching the app ...");
  }

  @Override
  public void start(final Stage primaryStage) throws Exception {
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
