package edu.cuny.brooklyn.io;

import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FileLocksDemoCLI {
	private final static Logger LOGGER = LoggerFactory.getLogger(FileLocksDemoCLI.class);

	public static void main(String[] args) {
		LOGGER.debug("FileLocksDemoCLI starts.");

		if (args.length < 2) {
			System.out.println("Usage: <long_numbers_bin_file> <n-th_number>");
			System.exit(-1);
		}

		FileLocksDemoCLI demo = new FileLocksDemoCLI();
		try {
			demo.update(args[0], Integer.parseInt(args[1]));
		} catch (FileNotFoundException e) {
			System.err.println("File not found: " + e.getMessage());
			LOGGER.error("File not found: " + e.getMessage(), e);
		} catch (EOFException e) {
			System.err.println("The file does not have enough data to read: " + e.getMessage());
			LOGGER.error("The file does not have enough data to read: " + e.getMessage(), e);
		} catch (IOException e) {
			System.err.println("I/O error: " + e.getMessage());
			LOGGER.error("I/O error: " + e.getMessage(), e);
		} catch (NumberFormatException e) {
			System.err.println("The number is not an integer: " + e.getMessage());
			LOGGER.error("The number is not an integer: " + e.getMessage(), e);
		} 

		LOGGER.debug("FileLocksDemoCLI exits.");
	}

	private void update(String filename, int index) throws FileNotFoundException, IOException {
		RandomAccessFile raf = null;
		FileChannel ch = null;
		FileLock exclusiveLock = null;
		FileLock sharedLock = null;
		try {
			raf = new RandomAccessFile(filename, "rw");

			int numNumbers = raf.readInt();
			if (index >= numNumbers) {
				throw new IllegalArgumentException("The index is too big for the file.");
			}
			int position = Integer.SIZE / 8 + index * Long.SIZE / 8;
			int size = Long.SIZE / 8;
			boolean shared = true;
			ch = raf.getChannel();

			exclusiveLock = ch.lock(position, size, !shared);

			raf.seek(position);
			long num = raf.readLong();
			System.out.println("Before the write, the number is " + num);
			num++;
			raf.seek(position);
			raf.writeLong(num);
			exclusiveLock.release();
			
			sharedLock = ch.lock(position, size, shared);
			raf.seek(position);
			num = raf.readLong();
			System.out.println("After the write, the number is " + num);
			sharedLock.release();
		} finally {
			if (exclusiveLock != null && exclusiveLock.isValid()) exclusiveLock.release();
			if (sharedLock != null && sharedLock.isValid()) sharedLock.release();
			if (ch != null) ch.close();
			if (raf != null) raf.close();
		}
	}
}
