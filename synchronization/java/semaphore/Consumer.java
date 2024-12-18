public final class Consumer<T> implements Runnable {
  private BoundedBuffer<T> buffer;
  private java.util.function.Consumer<T> itemConsumer;
  private int numItemsToConsume;

  public Consumer(
      final BoundedBuffer<T> buffer,
      final int numItemsToConsume,
      final java.util.function.Consumer<T> itemConsumer) {
    this.buffer = buffer;
    this.itemConsumer = itemConsumer;
    this.numItemsToConsume = numItemsToConsume;
  }

  public void run() {
    T item = null;
    for (int i = 0; i < numItemsToConsume; i++) {
      try {
        item = buffer.remove();
      } catch (InterruptedException e) {
        // ignoring it
        break;
      }
      itemConsumer.accept(item);
    }
  }
}
