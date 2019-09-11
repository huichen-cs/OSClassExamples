public class DecimalToBinary {
  public static void main(String[] args) {
      if (args.length < 1) {
          usage();
          return;
      }

      for (int i=0; i<args.length; i++) {
          int n = Integer.parseInt(args[i]);
          System.out.println("(" + n + ")10 = (" + decimalToBinary(n) + ")2");
      }
  }

  private static void usage() {
    System.out.println("Usage: tobinary <decimal number 1> <decimal number 2> ...");
  }

  private static String decimalToBinary(int n) {
      int nbits = Integer.SIZE - 1;
      while ((n & (1 << nbits)) == 0 && nbits > 0) {
          nbits --;
      }

      StringBuilder sb = new StringBuilder();

      while (nbits >= 0) {
          sb.append(((n >> nbits) & 1));
          nbits --;
      }

      return sb.toString();
  }
}
