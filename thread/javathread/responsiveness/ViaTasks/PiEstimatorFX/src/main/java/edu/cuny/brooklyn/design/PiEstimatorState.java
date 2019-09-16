package edu.cuny.brooklyn.design;

import java.util.Objects;

public class PiEstimatorState {
//	private final static Logger LOGGER = LoggerFactory.getLogger(PiEstimatorState.class);
	private double x;
	private double y;
	private boolean isAccepted;
	private long numOfAccepted;
	
	public PiEstimatorState(double x, double y, boolean isAccepted, long numOfAccepted) {
		this.x = x;
		this.y = y;
		this.isAccepted = isAccepted;
		this.numOfAccepted = numOfAccepted;
	}

	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}

	public boolean isAccepted() {
		return isAccepted;
	}

	public long getNumOfAccepted() {
		return numOfAccepted;
	}
	
	public void update(double x, double y, boolean isAccepted, long numOfAccepted) {
		this.x = x;
		this.y = y;
		this.isAccepted = isAccepted;
		this.numOfAccepted = numOfAccepted;
	}
	
	@Override
	public boolean equals(Object theOther) {
//		LOGGER.debug("equals called");
		if (!(theOther instanceof PiEstimatorState)) {
			return false;
		}
		PiEstimatorState rhs = (PiEstimatorState) theOther;
		if (Double.compare(x, rhs.x) != 0) {
			return false;
		}
		if (Double.compare(y, rhs.y) != 0) {
			return false;
		}
		if (isAccepted != rhs.isAccepted) {
			return false;
		}
		if (numOfAccepted != rhs.numOfAccepted) {
			return false;
		}
		return true;
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(x, y, isAccepted, numOfAccepted);
	}
}
