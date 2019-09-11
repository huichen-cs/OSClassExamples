import java.lang.reflect.Array;
import java.util.concurrent.Semaphore;

public class BoundedBuffer<T> {
    private T[] buffer;
    private int in;
    private int out;

    private Semaphore mutex;
    private Semaphore empty;
    private Semaphore full;

    @SuppressWarnings("unchecked")
    public BoundedBuffer(Class<T> clazz, int bufferSize) {
        if (bufferSize <= 0) {
            throw new IllegalArgumentException("bufferSize " + bufferSize + 
                    " is less than or equal to 0");
        }
        buffer = (T[]) Array.newInstance(clazz, bufferSize);
        in = 0;
        out = 0;

        mutex = new Semaphore(1);
        empty = new Semaphore(bufferSize);
        full  = new Semaphore(0);
    }

    public void insert(T t) throws InterruptedException {
      try {
        empty.acquire();  

        try {
          mutex.acquire();
    
          buffer[in] = t;
          in = (in + 1) % buffer.length;
        } finally {
          mutex.release();
        }
      } finally {
        full.release();
      }
    }


    public T remove() throws InterruptedException {
        T t = null;
        try {
          full.acquire();

          try {
            mutex.acquire();

            t = buffer[out];
            out = (out + 1) % buffer.length;
          } finally {
            mutex.release();
          }
        } finally {
          empty.release();
        }

        return t;
    }
}
