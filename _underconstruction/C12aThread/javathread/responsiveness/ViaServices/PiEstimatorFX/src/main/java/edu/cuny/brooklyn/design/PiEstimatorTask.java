package edu.cuny.brooklyn.design;

import java.util.Random;

import javafx.concurrent.Task;

public class PiEstimatorTask extends Task<PiEstimatorState>{
	// private final static Logger LOGGER = LoggerFactory.getLogger(PiEstimatorTask.class);
	
	private final long numOfPoints;
	private final Random rngX;
	private final Random rngY;

	public PiEstimatorTask(long numOfPoints, long seedX, long seedY) {
		this.numOfPoints = numOfPoints;
		this.rngX = new Random(seedX);
		this.rngY = new Random(seedY);
	}
	
	@Override
	protected PiEstimatorState call() throws Exception {
		long accepted = 0;
		for (long i = 0; i < numOfPoints; i++) {
			if (isCancelled()) {
				break;
			}
			
			double x = rngX.nextDouble();
			double y = rngY.nextDouble();
			boolean isAccepted = false;
			if (x * x + y * y < 1.0) {
				accepted++;
				isAccepted = true;
			} 
			updateProgress(i, numOfPoints-1);
			updateValue(new PiEstimatorState(x, y, isAccepted, accepted));
			// LOGGER.debug("x = " + x + ", y = " + y);
		}
		return new PiEstimatorState(-1., -1., false, accepted);
	}
	
	@Override
	protected void succeeded() {
		super.succeeded();
		double pi = (double) getValue().getNumOfAccepted() / (double) numOfPoints * 4.0;
		updateMessage(Double.toString(pi));
	}

}
