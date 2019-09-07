package edu.cuny.brooklyn.design;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

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

public class PiEstimatorView {
	private final static Logger LOGGER = LoggerFactory.getLogger(PiEstimatorView.class);
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
	private ChangeListener<PiEstimatorState> plotPointListener = (obsv, oldv, newv) -> plotPoint(newv);
	
	public PiEstimatorView() {
		HBox hbox = new HBox();
		hbox.setPadding(new Insets(20., 20., 20., 20.));
		
		GridPane pane = new GridPane();
		pane.setPadding(new Insets(20., 20., 20., 20.));
		pane.setVgap(5.);
		pane.setHgap(5.);
		

		RowConstraints rowConstraints = new RowConstraints(20.);
		rowConstraints.setVgrow(Priority.ALWAYS);
		for (int i=0; i<20; i++) {
			pane.getRowConstraints().add(rowConstraints);
		}
		
		progressBar = new ProgressBar();
		progressBar.setProgress(0.);
		progressBar.setMaxWidth(Double.MAX_VALUE);
		pane.add(progressBar, 0, 0, 2, 1);
		
		piValue = new Label("?");
		piValue.setAlignment(Pos.CENTER_LEFT);
		Label label = new Label("pi = ");
		label.setAlignment(Pos.CENTER_RIGHT);
		pane.add(label, 0, 1);
		GridPane.setHalignment(label, HPos.RIGHT);
		pane.add(piValue, 1, 1);
		GridPane.setHalignment(piValue, HPos.LEFT);
		
		pane.add(new Label("# of Points"), 0, 2, 2, 1);
		numOfPointsField = new TextField("1000000000");
		pane.add(numOfPointsField, 0, 3, 2, 1);
		
		pane.add(new Label("RNG Seed for X"), 0, 5, 2, 1);
		rngSeedXField = new TextField("111111");
		pane.add(rngSeedXField, 0, 6, 2, 1);
		
		pane.add(new Label("RNG Seed for Y"), 0, 8, 2, 1);
		rngSeedYField = new TextField("999999");
		pane.add(rngSeedYField, 0, 9, 2, 1);
		
		startButton = new Button("Start");
		pane.add(startButton, 0, 11);
		startButtonWithGraph = new Button("Start with Graph");
		pane.add(startButtonWithGraph, 1, 11);
		
		// little calculator
		operand1Field = new TextField("0.0");
		pane.add(operand1Field, 0, 15, 2, 1);
		pane.add(new Label("x"), 0, 16, 2, 1);
		operand2Field = new TextField("0.0");
		pane.add(operand2Field, 0, 17, 2, 1);
		pane.add(new Label("="),  0, 18);
		productResult = new Label();
		pane.add(productResult, 1, 18);
		productButton = new Button("Multiply");
		pane.add(productButton,  0,  19, 2, 1);
		
		canvas = new Canvas(600, 600);
		hbox.getChildren().addAll(canvas, pane);
		
		gc = canvas.getGraphicsContext2D();
		gc.setFill(Color.WHITE);
		gc.fillRect(0,  0,  canvas.getWidth(), canvas.getHeight());
		gc.beginPath();
		gc.setStroke(Color.BLACK);
		gc.moveTo(0,  0);
		gc.arc(0, 0, canvas.getWidth(), canvas.getWidth(), 270, 90);
		gc.closePath();
		gc.stroke();
		
		scene = new Scene(hbox);
		
		startButton.setOnAction(e -> estimatePi(null));
		startButtonWithGraph.setOnAction(e->estimatePi(gc));
		productButton.setOnAction(e -> doMultiply());
	}
	

	public void setPiEstimatorService(PiEstimatorService service) {
		if (service == null) {
			throw new IllegalArgumentException("PiEstimatorService service must not be null.");
		}
		workerService = service;
	}

	public void showOn(Stage stage) {
		stage.setTitle("Simple Monte Carlo PI Estimator");
		stage.setScene(scene);
		stage.show();
	}
	
	private void estimatePi(GraphicsContext gc) {
		String fieldText = numOfPointsField.getText();
		long numOfPoints = 1000000000l;
		if (!fieldText.isEmpty()) {
			numOfPoints = Long.parseLong(fieldText);
		}
		
		fieldText = rngSeedXField.getText();
		long seedX = 1111111;
		if (!fieldText.isEmpty()) {
			seedX = Long.parseLong(fieldText);
		}
		
		fieldText = rngSeedYField.getText();
		long seedY = 1111111;
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
	
	private void plotPoint(PiEstimatorState state) {
		if (state == null) {
			return;
		}
		if (state.getX() < 0. || state.getY() < 0.) return;
		if (state.isAccepted()) {
			gc.setFill(Color.RED);
		} else {
			gc.setFill(Color.BLUE);
		}
		int w = (int)(state.getX() * canvas.getWidth());
		int h = (int)(state.getY() * canvas.getHeight());
		// LOGGER.debug("x = " + state.getX() + ", y = " + state.getY() + " w = " + w + ", h = " + h);
		gc.fillRect(w, h, 1,  1);
	}
	
	private void validatePiEstimatorService() {
		if (workerService ==  null) {
			throw new RuntimeException("PiEstimatorService must not be null.");
		}
	}
	
	private void resetGraph() {
		gc.setFill(Color.WHITE);
		gc.fillRect(0,  0,  canvas.getWidth(), canvas.getHeight());
		gc.beginPath();
		gc.setStroke(Color.BLACK);
		gc.moveTo(0,  0);
		gc.arc(0, 0, canvas.getWidth(), canvas.getWidth(), 270, 90);
		gc.closePath();
		gc.stroke();
	}

}
