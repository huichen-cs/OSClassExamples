import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Supplier;

public class Producer<T> implements Runnable {
    private AtomicBoolean running; 

    private BoundedBuffer<T> buffer;
    private Supplier<T> supplier;

    public Producer(BoundedBuffer<T> buffer, Supplier<T> supplier) {
        this.buffer = buffer;
        this.supplier = supplier;
        this.running = new AtomicBoolean(false);
    }

    public void run() {
        running.set(true);

        while(running.get()) {
            T item = supplier.get();
            try {
              buffer.insert(item);
            } catch (InterruptedException e) { 
                // ignoring it 
                running.set(false); 
                break;
            }
        }
    }

    public void interrupt() {
        running.set(false);
    }
}
