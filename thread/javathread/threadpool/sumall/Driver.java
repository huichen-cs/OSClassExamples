import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/**
 * Revised based on the sample code in Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin.
 * Operating system concepts. Wiley, 2018.
 */
class Summation implements Callable<Integer> {

  private int upper;

  Summation(final int upper) {
    this.upper = upper;
  }

  /* The thread will execute in this method */
  public Integer call() {
    int sum = 0;

    for (int i = 1; i <= upper; i++) {
      sum += i;
    }

    return Integer.valueOf(sum);
  }
}

public class Driver {

  public static void main(final String[] args) {

    if (args.length == 0) {
      System.out.println("Usage: Driver number");
      return;
    }

    int upper = Integer.parseInt(args[0]);

    ExecutorService pool = Executors.newSingleThreadExecutor();

    Future<Integer> result = pool.submit(new Summation(upper));

    try {

      System.out.println("sum = " + result.get());

    } catch (InterruptedException | ExecutionException ie) {
    }

    pool.shutdown();
  }
}
