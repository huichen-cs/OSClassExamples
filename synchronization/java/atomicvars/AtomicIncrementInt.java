import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class AtomicIncrementInt {
    private final static int THREAD_POOL_SIZE = 4;
    private final static int DEFAULT_THREAD_NUM = 50;
    private static AtomicInteger countOfServiceCalled = new AtomicInteger(0);
    private static AtomicInteger nextThreadId = new AtomicInteger(0);
    private static int sum = 0;

    public static void main(String[] args ) throws InterruptedException {
        int numOfThreads = DEFAULT_THREAD_NUM;
        if (args.length > 0) {
           numOfThreads = Integer.parseInt(args[0]); 
        }
        Runnable[] serviceThreads = new Runnable[numOfThreads];
        for (int i=0; i<serviceThreads.length; i++) {
            serviceThreads[i] = new ServiceRunnable();
        }

        ExecutorService executor = 
            Executors.newFixedThreadPool(THREAD_POOL_SIZE);

        System.out.println("Ready to run threads");

        for (Runnable runnable: serviceThreads) {
            executor.execute(runnable);
        }

        executor.shutdown();

        while (!executor.isTerminated()); 

        System.out.println(countOfServiceCalled);
        System.out.println(nextThreadId);
        System.out.println(sum);
    }
    
    private static void service() {
        countOfServiceCalled.incrementAndGet();
        // do something useless
        int n = (int)(Math.random() * 10); 
        for (int i=0; i<n; i++) {
            sum += (int)(Math.random() * 3);
        }    
    }

    static class ServiceRunnable implements Runnable {
        private int threadId;
        
        public void run() { 
            threadId = nextThreadId.incrementAndGet();
            for (int i=0; i<100000; i++) service(); 
            System.out.println("In Thread " + threadId);
        }
    }
}
