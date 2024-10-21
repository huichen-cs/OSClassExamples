import java.util.Random;

public class SumTaskClient {
  private static final int MAX_RANDOM_NUM = 100;

  public static void main(final String[] args) {
    if (args.length < 1) {
      System.out.println("Usage: SumTaskClient <numbers of numbers>");
      System.exit(1);
    }

    int numNumbers = Integer.parseInt(args[0]);
    System.out.println("To sum " + numNumbers + " random numbers.");

    int[] numbers = makeRandomArray(numNumbers);

    SumTask task = new SumTask(0, numbers.length - 1, numbers);

    long sum = task.compute();
    System.out.println("From SumTask: Sum = " + sum);

    sum = sumArray(numbers);
    System.out.println("From Main: Sum = " + sum);
  }

  private static int[] makeRandomArray(final int numNumbers) {
    int[] numbers = new int[numNumbers];
    Random rng = new Random();
    for (int i = 0; i < numbers.length; i++) {
      numbers[i] = rng.nextInt(MAX_RANDOM_NUM);
    }
    return numbers;
  }

  private static long sumArray(final int[] numbers) {
    long sum = 0;
    for (int n : numbers) {
      sum += n;
    }
    return sum;
  }
}
