import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class AtomicIncrementInt {
  private static final int THREAD_POOL_SIZE = 4;
  private static final int DEFAULT_THREAD_NUM = 50;
  private static final int NUM_SERVICE_CALLS = 100000;
  private static final int FACTOR_1 = 10;
  private static final int FACTOR_2 = 3;
  private static AtomicInteger countOfServiceCalled = new AtomicInteger(0);
  private static AtomicInteger nextThreadId = new AtomicInteger(0);
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

    System.out.println("Ready to run threads");

    for (Runnable runnable : serviceThreads) {
      executor.execute(runnable);
    }

    executor.shutdown();

    while (!executor.isTerminated()) {
      ;
    }

    System.out.println(countOfServiceCalled);
    System.out.println(nextThreadId);
    System.out.println(sum);
  }

  private static void service() {
    countOfServiceCalled.incrementAndGet();
    // do something useless
    int n = (int) (Math.random() * FACTOR_1);
    for (int i = 0; i < n; i++) {
      sum += (int) (Math.random() * FACTOR_2);
    }
  }

  static class ServiceRunnable implements Runnable {
    private int threadId;

    public void run() {
      threadId = nextThreadId.incrementAndGet();
      for (int i = 0; i < NUM_SERVICE_CALLS; i++) {
        service();
      }
      System.out.println("In Thread " + threadId);
    }
  }
}
