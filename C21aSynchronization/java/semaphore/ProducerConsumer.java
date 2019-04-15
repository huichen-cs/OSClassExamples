public class ProducerConsumer {

    private int numItemsConsumed;

    private BoundedBuffer<Integer> buffer;

    private Producer<Integer> producer;
    private Consumer<Integer> consumer;

    private int item;
    private int sum;

    public static void main(String[] args) {
        final int bufferSize = 100;
        final int numItemsConsumed = 10000;

        ProducerConsumer pc = new ProducerConsumer(bufferSize, numItemsConsumed);
        pc.run();
        System.out.println("The sum is " + pc.sum);
    }

    public ProducerConsumer(int bufferSize, int numItemsConsumed) {
        /* initialize the bounded buffer shared by producer & consumer */
        this.buffer = new BoundedBuffer<Integer>(Integer.class, bufferSize);

        /* create the producer and consumer objects */
        this.item = 0;
        this.producer = new Producer<Integer>(buffer, () -> item ++);

        this.sum = 0;
        this.consumer = new Consumer<Integer>(buffer, numItemsConsumed, 
                item -> sum += item);
    }

    private void run() {
        Thread producerThread = new Thread(this.producer);
        Thread consumerThread = new Thread(this.consumer);

        producerThread.start();
        consumerThread.start();
        try {
            consumerThread.join();
        } catch (InterruptedException e) {
        }
        producer.interrupt();
        producerThread.interrupt();
    }
}
