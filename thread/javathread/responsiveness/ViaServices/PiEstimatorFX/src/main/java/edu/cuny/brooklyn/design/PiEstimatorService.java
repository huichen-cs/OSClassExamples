package edu.cuny.brooklyn.design;

import javafx.beans.property.LongProperty;
import javafx.beans.property.SimpleLongProperty;
import javafx.concurrent.Service;
import javafx.concurrent.Task;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public final class PiEstimatorService extends Service<PiEstimatorState> {
  private static final Logger LOGGER = LoggerFactory.getLogger(PiEstimatorService.class);

  private LongProperty numOfPoints = new SimpleLongProperty();
  private LongProperty seedX = new SimpleLongProperty();
  private LongProperty seedY = new SimpleLongProperty();

  public long getNumOfPoints() {
    return numOfPoints.get();
  }

  public long getSeedX() {
    return seedX.get();
  }

  public void setNumOfPoints(final long numOfPointsValue) {
    numOfPoints.set(numOfPointsValue);
  }

  public void setSeedX(final long seedXValue) {
    seedX.set(seedXValue);
  }

  public void setSeedY(final long seedYValue) {
    seedX.set(seedYValue);
  }

  public LongProperty numOfPointsProperty() {
    return numOfPoints;
  }

  public LongProperty seedXProperty() {
    return seedX;
  }

  public LongProperty seedYProperty() {
    return seedY;
  }

  @Override
  protected Task<PiEstimatorState> createTask() {
    PiEstimatorTask task = new PiEstimatorTask(numOfPoints.get(), seedX.get(), seedY.get());
    return task;
  }

  @Override
  protected void cancelled() {
    LOGGER.debug("PiEstimatorState service cancelled its task.");
  }

  @Override
  protected void failed() {
    LOGGER.debug("PiEstimatorState service failed its task.");
  }

  @Override
  protected void succeeded() {
    LOGGER.debug("PiEstimatorState service successfully completed its task.");
  }
}
