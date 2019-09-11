package edu.cuny.brooklyn.io;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

public class LongIntegerFileSeeker {
	private RandomAccessFile randAccessFile;

	public LongIntegerFileSeeker(String filename) throws FileNotFoundException {
		randAccessFile = new RandomAccessFile(filename, "r");
	}

	public long readIntegerFile(String filename, int n) throws IOException {
		long number = 0;
		
		System.out.format("The file has %d bytes%n", randAccessFile.length());
		System.out.format("The file pointer is at byte %d.%n", randAccessFile.getFilePointer());
		
		randAccessFile.seek(Long.SIZE / 8 * n + Integer.SIZE / 8);
		
		System.out.format("The file pointer is at byte %d after the seek.%n", randAccessFile.getFilePointer());
		
		number = randAccessFile.readLong();
		
		System.out.format("The file pointer is at byte %d after the read.%n", randAccessFile.getFilePointer());
		
		return number;
	}
	
	public void close() throws IOException {
		randAccessFile.close();
	}
}
