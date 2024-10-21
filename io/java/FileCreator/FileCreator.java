import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

class FileCreator {
  private static final int BUF_SIZE_EXPONENT = 20;

  public static void main(final String[] args) throws FileNotFoundException, IOException {
    if (args.length < 2) {
      System.out.println("Usage: FileCreator filename size_MBs");
      System.exit(0);
    }

    File file = new File(args[0]);
    int size = Integer.parseInt(args[1]);
    byte[] data = new byte[1 << BUF_SIZE_EXPONENT];

    try (FileOutputStream os = new FileOutputStream(file)) {
      for (int i = 0; i < size; i++) {
        os.write(data);
      }
    }
  }
}
