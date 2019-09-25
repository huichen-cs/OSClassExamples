/**
 * Revised based on the sample code in 
 *   Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *   concepts. Wiley, 2018.
 */
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.atomic.AtomicInteger;

public class SumTask extends RecursiveTask<Long> {
	final static int THRESHOLD = 10000;
    static AtomicInteger taskNo = new AtomicInteger(0);

	private int begin;
	private int end;
	private int[] array;

	public SumTask(int begin, int end, int[] array) {
		this.begin = begin;
		this.end = end;
		this.array = array;
	}

	public Long compute() {
        System.out.println("In task " + taskNo.getAndIncrement());
		if (end - begin < THRESHOLD) {
			long sum = 0;
			for (int i = begin; i <= end; i++) {
				sum += array[i];
            }

			return sum;
		} else {
			int mid = (begin + end) / 2;

			SumTask leftTask = new SumTask(begin, mid, array);
			SumTask rightTask = new SumTask(mid + 1, end, array);
			leftTask.fork();
			rightTask.fork();

			return rightTask.join() + leftTask.join();
		}
	}
}


