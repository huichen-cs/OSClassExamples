import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class ProducerConsumer {
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition fullCond = lock.newCondition();
    private final Condition emptyCond = lock.newCondition();

    public static void main(String[] args) {
        ProducerConsumer pc =  new ProducerConsumer();
        Producer producer = pc.new Producer(); 
        Consumer consumer = pc.new Consumer(10); 
        Thread p = new Thread(producer);
        Thread c = new Thread(consumer);

        p.start(); c.start();
        try {
            c.join(); 
            System.out.println("The sum is " + consumer.getSum());
            producer.interrupt();
            p.interrupt();
        } catch (InterruptedException e) {
        }
    }


    private int buffer = 0;

    private class Producer implements Runnable {
        private AtomicBoolean running;

        public Producer() {
            running = new AtomicBoolean(false);
        }

        public void interrupt() {
            running.set(false);
            if (lock.isLocked()) lock.unlock();
        }

        public void run() {
            int count = 0;
            running.set(true);
            try {
                while(running.get()) {
                    lock.lock();
                    while (buffer != 0) 
                        fullCond.await(); /* buffer full, wait ... */
                    try {
                        buffer = ++ count; /* produce and insert to buffer */
                    } finally {
                        emptyCond.signal();
                        lock.unlock();
                    }
                }
            } catch (InterruptedException e) { }
        }
    }

    private class Consumer implements Runnable {
        private int max;
        private int sum;

        public Consumer(int max) {
            this.max = max;
        }

        public int getSum() {
            return sum;
        }

        public void run() {
            int item = 0;
            sum = 0;
            try {
                for (int i=0; i<max; i++) {
                    lock.lock();
                    while (buffer == 0) 
                        emptyCond.await();
                    try {
                        item = buffer;
                        buffer = 0;
                    } finally {
                        fullCond.signal();
                        lock.unlock();
                    }
                    sum += item;
                }
            } catch (InterruptedException e) {
            }
        }
    }
}
