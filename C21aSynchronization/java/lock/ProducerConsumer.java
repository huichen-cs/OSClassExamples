import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
    private final ReentrantLock lock = new ReentrantLock();

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
            while(running.get()) {
                while (running.get() && buffer != 0) ;  /* buffer full ... */
                lock.lock();
                try {
                    buffer = ++ count; /* produce an item, insert to buffer */
                } finally {
                    lock.unlock();
                }
            }
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
            for (int i=0; i<max; i++) {
                while (buffer == 0) ; /* buffer empty, busy waiting */
                lock.lock();
                try {
                    item = buffer;
                    buffer = 0;
                } finally {
                    lock.unlock();
                }
                sum += item;
            }
        }
    }
}
