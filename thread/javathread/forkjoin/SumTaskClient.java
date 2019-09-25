import java.util.Random;

public class SumTaskClient {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: SumTaskClient <numbers of numbers>");
            System.exit(1);
        }

        int numNumbers = Integer.parseInt(args[0]);
        System.out.println("To sum " + numNumbers + " random numbers.");

        int[] numbers = makeRandomArray(numNumbers);

        SumTask task = new SumTask(0, numbers.length-1, numbers);

        long sum = task.compute();
        System.out.println("From SumTask: Sum = " + sum);

        sum = sumArray(numbers);
        System.out.println("From Main: Sum = " + sum);
    }

    private static int[] makeRandomArray(int numNumbers) {
        int[] numbers = new int[numNumbers];
        Random rng = new Random();
        for (int i=0; i<numbers.length; i++) {
            numbers[i] = rng.nextInt(100);
        }
        return numbers;
    }

    private static long sumArray(int[] numbers) {
        long sum = 0;
        for (int n: numbers) {
            sum += n;
        }
        return sum;
    }
}
