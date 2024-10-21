package edu.cuny.brooklyn.design;

import javafx.beans.value.ChangeListener;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.RowConstraints;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public final class PiEstimatorView {
  private static final Logger LOGGER = LoggerFactory.getLogger(PiEstimatorView.class);
  private static final int ARC_ANGLE = 270;
  private static final int ARC_LENGTH = 90;
  private static final int X_RANDOM_SEED = 1111111;
  private static final int Y_RANDOM_SEED = 1111111;
  private static final double PADDING_SIZE = 20.;
  private static final double GAP_SIZE = 5.;
  private static final double CONSTRAINT_SIZE = 20.;
  private static final int NUM_ROWS = 20;
  private static final long NUM_RANDOM_POINTS = 1000000000L;
  private static final int CANVAS_SIZE = 600;
  private static final int PBAR_COL = 0;
  private static final int PBAR_ROW = 0;
  private static final int PI_COL = 1;
  private static final int PI_ROW = 1;
  private static final int NUM_POINTS_COL = 0;
  private static final int NUM_POINTS_ROW = 3;
  private static final int X_RANDOM_SEED_COL = 0;
  private static final int X_RANDOM_SEED_ROW = 6;
  private static final int Y_RANDOM_SEED_COL = 0;
  private static final int Y_RANDOM_SEED_ROW = 9;
  private static final int START_BTN_COL = 0;
  private static final int START_BTN_ROW = 11;
  private static final int START_GRAPH_BTN_COL = 1;
  private static final int START_GRAPH_BTN_ROW = 11;
  private static final int OPERAND_1_COL = 0;
  private static final int OPERAND_1_ROW = 15;
  private static final int OPERATOR_COL = 0;
  private static final int OPERATOR_ROW = 16;
  private static final int OPERAND_2_COL = 0;
  private static final int OPERAND_2_ROW = 17;
  private static final int PRODUCT_RESULT_COL = 1;
  private static final int PRODUCT_RESULT_ROW = 18;
  private static final int PRODUCT_BTN_COL = 0;
  private static final int PRODUCT_BTN_ROW = 19;
  private static final int PRODUCT_BTN_COLSPAN = 2;
  private static final int PRODUCT_BTN_ROWSPAN = 1;
  private Scene scene;
  private Label piValue;
  private TextField numOfPointsField;
  private TextField rngSeedXField;
  private TextField rngSeedYField;
  private Button startButton;
  private Button startButtonWithGraph;
  private Canvas canvas;
  private GraphicsContext gc;

  private TextField operand1Field;
  private TextField operand2Field;
  private Label productResult;
  private Button productButton;

  private ProgressBar progressBar;

  private PiEstimatorService workerService;
  private ChangeListener<PiEstimatorState> plotPointListener =
      (obsv, oldv, newv) -> plotPoint(newv);

  public PiEstimatorView() {
    HBox hbox = new HBox();
    hbox.setPadding(new Insets(PADDING_SIZE, PADDING_SIZE, PADDING_SIZE, PADDING_SIZE));

    GridPane pane = new GridPane();
    pane.setPadding(new Insets(PADDING_SIZE, PADDING_SIZE, PADDING_SIZE, PADDING_SIZE));
    pane.setVgap(GAP_SIZE);
    pane.setHgap(GAP_SIZE);

    RowConstraints rowConstraints = new RowConstraints(CONSTRAINT_SIZE);
    rowConstraints.setVgrow(Priority.ALWAYS);
    for (int i = 0; i < NUM_ROWS; i++) {
      pane.getRowConstraints().add(rowConstraints);
    }

    progressBar = new ProgressBar();
    progressBar.setProgress(0.);
    progressBar.setMaxWidth(Double.MAX_VALUE);
    pane.add(progressBar, PBAR_COL, PBAR_ROW, 2, 1);

    piValue = new Label("?");
    piValue.setAlignment(Pos.CENTER_LEFT);
    Label label = new Label("pi = ");
    label.setAlignment(Pos.CENTER_RIGHT);
    pane.add(label, PI_COL - 1, PI_ROW);
    GridPane.setHalignment(label, HPos.RIGHT);
    pane.add(piValue, PI_COL, PI_ROW);
    GridPane.setHalignment(piValue, HPos.LEFT);

    pane.add(new Label("# of Points"), NUM_POINTS_COL, NUM_POINTS_ROW - 1, 2, 1);
    numOfPointsField = new TextField("1000000000");
    pane.add(numOfPointsField, NUM_POINTS_COL, NUM_POINTS_ROW, 2, 1);

    pane.add(new Label("RNG Seed for X"), X_RANDOM_SEED_COL, X_RANDOM_SEED_ROW - 1, 2, 1);
    rngSeedXField = new TextField("111111");
    pane.add(rngSeedXField, X_RANDOM_SEED_COL, X_RANDOM_SEED_ROW, 2, 1);

    pane.add(new Label("RNG Seed for Y"), Y_RANDOM_SEED_COL, Y_RANDOM_SEED_ROW - 1, 2, 1);
    rngSeedYField = new TextField("999999");
    pane.add(rngSeedYField, Y_RANDOM_SEED_COL, Y_RANDOM_SEED_ROW, 2, 1);

    startButton = new Button("Start");
    pane.add(startButton, START_BTN_COL, START_BTN_ROW);
    startButtonWithGraph = new Button("Start with Graph");
    pane.add(startButtonWithGraph, START_GRAPH_BTN_COL, START_GRAPH_BTN_ROW);

    // little calculator
    operand1Field = new TextField("0.0");
    pane.add(operand1Field, OPERAND_1_COL, OPERAND_1_ROW, 2, 1);
    pane.add(new Label("x"), OPERATOR_COL, OPERATOR_ROW, 2, 1);
    operand2Field = new TextField("0.0");
    pane.add(operand2Field, OPERAND_2_COL, OPERAND_2_ROW, 2, 1);
    pane.add(new Label("="), PRODUCT_RESULT_COL - 1, PRODUCT_RESULT_ROW);
    productResult = new Label();
    pane.add(productResult, PRODUCT_RESULT_COL, PRODUCT_RESULT_ROW);
    productButton = new Button("Multiply");
    pane.add(
        productButton, PRODUCT_BTN_COL, PRODUCT_BTN_ROW, PRODUCT_BTN_COLSPAN, PRODUCT_BTN_ROWSPAN);

    canvas = new Canvas(CANVAS_SIZE, CANVAS_SIZE);
    hbox.getChildren().addAll(canvas, pane);

    gc = canvas.getGraphicsContext2D();
    gc.setFill(Color.WHITE);
    gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
    gc.beginPath();
    gc.setStroke(Color.BLACK);
    gc.moveTo(0, 0);
    gc.arc(0, 0, canvas.getWidth(), canvas.getWidth(), ARC_ANGLE, ARC_LENGTH);
    gc.closePath();
    gc.stroke();

    scene = new Scene(hbox);

    startButton.setOnAction(e -> estimatePi(null));
    startButtonWithGraph.setOnAction(e -> estimatePi(gc));
    productButton.setOnAction(e -> doMultiply());
  }

  public void setPiEstimatorService(final PiEstimatorService service) {
    if (service == null) {
      throw new IllegalArgumentException("PiEstimatorService service must not be null.");
    }
    workerService = service;
  }

  public void showOn(final Stage stage) {
    stage.setTitle("Simple Monte Carlo PI Estimator");
    stage.setScene(scene);
    stage.show();
  }

  private void estimatePi(final GraphicsContext gc) {
    String fieldText = numOfPointsField.getText();
    long numOfPoints = NUM_RANDOM_POINTS;
    if (!fieldText.isEmpty()) {
      numOfPoints = Long.parseLong(fieldText);
    }

    fieldText = rngSeedXField.getText();
    long seedX = X_RANDOM_SEED;
    if (!fieldText.isEmpty()) {
      seedX = Long.parseLong(fieldText);
    }

    fieldText = rngSeedYField.getText();
    long seedY = Y_RANDOM_SEED;
    if (!fieldText.isEmpty()) {
      seedY = Long.parseLong(fieldText);
    }

    LOGGER.debug("Start running PI estimator ...");

    validatePiEstimatorService();
    workerService.setNumOfPoints(numOfPoints);
    workerService.setSeedX(seedX);
    workerService.setSeedY(seedY);

    resetGraph();
    workerService.restart();
    progressBar.progressProperty().bind(workerService.progressProperty());
    piValue.textProperty().bind(workerService.messageProperty());
    if (gc != null) {
      workerService.valueProperty().removeListener(plotPointListener);
      workerService.valueProperty().addListener(plotPointListener);
    }

    LOGGER.debug("running PI estimator in background ...");
  }

  private void doMultiply() {
    String fieldText = operand1Field.getText();
    double operand1 = 0.0;
    if (!fieldText.isEmpty()) {
      operand1 = Double.parseDouble(fieldText);
    }
    fieldText = operand2Field.getText();
    double operand2 = 0.0;
    if (!fieldText.isEmpty()) {
      operand2 = Double.parseDouble(fieldText);
    }
    double product = operand1 * operand2;
    productResult.setText(Double.toString(product));
  }

  private void plotPoint(final PiEstimatorState state) {
    if (state == null) {
      return;
    }
    if (state.getX() < 0. || state.getY() < 0.) {
      return;
    }
    if (state.isAccepted()) {
      gc.setFill(Color.RED);
    } else {
      gc.setFill(Color.BLUE);
    }
    int w = (int) (state.getX() * canvas.getWidth());
    int h = (int) (state.getY() * canvas.getHeight());
    // LOGGER.debug("x = " + state.getX() + ", y = " + state.getY() + " w = " + w + ", h = " + h);
    gc.fillRect(w, h, 1, 1);
  }

  private void validatePiEstimatorService() {
    if (workerService == null) {
      throw new RuntimeException("PiEstimatorService must not be null.");
    }
  }

  private void resetGraph() {
    gc.setFill(Color.WHITE);
    gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
    gc.beginPath();
    gc.setStroke(Color.BLACK);
    gc.moveTo(0, 0);
    gc.arc(0, 0, canvas.getWidth(), canvas.getWidth(), ARC_ANGLE, ARC_LENGTH);
    gc.closePath();
    gc.stroke();
  }
}
