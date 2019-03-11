/**
 * This is the sample program in page 138,
 *  Andrew S. Tanenbaum and Herbert Bos. 2014. Modern Operating Systems (4th
 *  ed.). Prentice Hall Press, Upper Saddle River, NJ, USA. 
 */
import java.util.Random;

public class ProducerConsumer {
    static final int N = 100;
    static Producer p = new Producer();
    static Consumer c = new Consumer();
    static ProducerConsumerMonitor monitor = new ProducerConsumerMonitor();

    public static void main(String[] args) {
        p.start();
        c.start();
    }

    static class Producer extends Thread {

        @Override
        public void run() {
            int item;
            while (true) {
                item = produceItem();
                monitor.insert(item);
            }
        }

        private int produceItem() {
            Random rng = new Random();
            return rng.nextInt();
        }
    }


    static class Consumer extends Thread {

        @Override
        public void run() {
            int item;
            while (true) {
                item = monitor.remove();
                consumeItem(item);
            }
        }

        private void consumeItem(int item) {
        }
    }

    static class ProducerConsumerMonitor {
        private int buffer[] = new int[N];
        private int count = 0, low = 0, high = 0;

        public synchronized void insert(int val) {
            if (count == N) {      // buffer is full, sleep while waiting
                goToSleep();
            }
            buffer[high] = val;    // insert the produced item to buffer
            high = (high + 1) / N; // advance to next available slot
            count = count + 1;     // count the number of items in buffer
            if (count == 1) {      
                // buffer is not empty any more, wake up consumer to consume
                notify();
            }
        }

        public synchronized int remove() {
            int val;

            if (count == 0) {
                goToSleep();
            }
            val = buffer[low];
            low = (low + 1) % N;
            count = count - 1;
            if (count == N - 1) { 
                // buffer is not full any more, wake up producer to produce
                notify();
            }
            return val;
        }

        private void goToSleep() {
            try {
                wait(); 
            } catch (InterruptedException e) {
            }
        }
    }
}

