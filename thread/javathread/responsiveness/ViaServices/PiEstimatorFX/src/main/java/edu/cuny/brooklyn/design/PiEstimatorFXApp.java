package edu.cuny.brooklyn.design;

import javafx.application.Application;
import javafx.stage.Stage;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public final class PiEstimatorFXApp extends Application {
  private static final Logger LOGGER = LoggerFactory.getLogger(PiEstimatorFXApp.class);

  public static void main(final String[] args) {
    launch(args);
  }

  @Override
  public void init() {
    LOGGER.info("Launching the app ...");
  }

  @Override
  public void start(final Stage primaryStage) throws Exception {
    PiEstimatorService service = new PiEstimatorService();
    PiEstimatorView view = new PiEstimatorView();
    view.setPiEstimatorService(service);
    view.showOn(primaryStage);
  }

  @Override
  public void stop() {
    LOGGER.info("Exiting the app...");
  }
}
