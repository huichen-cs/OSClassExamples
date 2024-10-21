package edu.cuny.brooklyn.io;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

public final class LongIntegerFileSeeker {
  private static final int NUM_BITS_PER_BYTE = 8;
  private RandomAccessFile randAccessFile;

  public LongIntegerFileSeeker(final String filename) throws FileNotFoundException {
    randAccessFile = new RandomAccessFile(filename, "r");
  }

  public long readIntegerFile(final String filename, final int n) throws IOException {
    long number = 0;

    System.out.format("The file has %d bytes%n", randAccessFile.length());
    System.out.format("The file pointer is at byte %d.%n", randAccessFile.getFilePointer());

    randAccessFile.seek(Long.SIZE / NUM_BITS_PER_BYTE * n + Integer.SIZE / NUM_BITS_PER_BYTE);

    System.out.format(
        "The file pointer is at byte %d after the seek.%n", randAccessFile.getFilePointer());

    number = randAccessFile.readLong();

    System.out.format(
        "The file pointer is at byte %d after the read.%n", randAccessFile.getFilePointer());

    return number;
  }

  public void close() throws IOException {
    randAccessFile.close();
  }
}
