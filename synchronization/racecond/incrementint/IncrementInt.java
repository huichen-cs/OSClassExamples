import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class IncrementInt {
  private static final int THREAD_POOL_SIZE = 4;
  private static final int DEFAULT_THREAD_NUM = 50;
  private static final int NUM_SERVICE_CALLS = 100000;
  private static final int FACTOR_1 = 10;
  private static final int FACTOR_2 = 3;
  private static int countOfServiceCalled = 0;
  private static int nextThreadId = 0;
  private static int sum = 0;

  public static void main(final String[] args) throws InterruptedException {
    int numOfThreads = DEFAULT_THREAD_NUM;
    if (args.length > 0) {
      numOfThreads = Integer.parseInt(args[0]);
    }
    Runnable[] serviceThreads = new Runnable[numOfThreads];
    for (int i = 0; i < serviceThreads.length; i++) {
      serviceThreads[i] = new ServiceRunnable();
    }

    ExecutorService executor = Executors.newFixedThreadPool(THREAD_POOL_SIZE);

    System.out.println(
        "Ready to run "
            + numOfThreads
            + " threads, "
            + "each of which calls service() 100000 times ...");

    for (Runnable runnable : serviceThreads) {
      executor.execute(runnable);
    }

    executor.shutdown();

    while (!executor.isTerminated()) {
      ;
    }

    System.out.println("countOfServiceCalled = " + countOfServiceCalled);
    System.out.println("nextThreadId = " + nextThreadId);
    System.out.println("sum = " + sum);
  }

  private static void service() {
    countOfServiceCalled++;
    // do something useless
    int n = (int) (Math.random() * FACTOR_1);
    for (int i = 0; i < n; i++) {
      sum += (int) (Math.random() * FACTOR_2);
    }
  }

  static class ServiceRunnable implements Runnable {
    private int threadId;

    public void run() {
      nextThreadId++;
      threadId = nextThreadId;
      for (int i = 0; i < NUM_SERVICE_CALLS; i++) {
        service();
      }
      System.out.println("In Thread " + threadId);
    }
  }
}
