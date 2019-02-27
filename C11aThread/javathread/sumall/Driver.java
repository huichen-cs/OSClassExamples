import java.util.concurrent.*;

class Summation implements Callable<Integer> {

  private int upper;

  public Summation(int upper) {
    this.upper = upper;
  }

  /* The thread will execute in this method */
  public Integer call() {
    int sum = 0;

    for (int i = 1; i <= upper; i++) {
      sum += i;
    }

    return new Integer(sum);
  }
}

public class Driver {

  public static void main(String[] args) {

     if (args.length == 0) {
         System.out.println("Usage: Driver number");
         return;
     }

     int upper = Integer.parseInt(args[0]);

     ExecutorService pool = Executors.newSingleThreadExecutor();

     Future<Integer> result = pool.submit(new Summation(upper));

     try {

       System.out.println("sum = " + result.get());

     } catch (InterruptedException | ExecutionException ie) { }

     pool.shutdown();
  }

}
