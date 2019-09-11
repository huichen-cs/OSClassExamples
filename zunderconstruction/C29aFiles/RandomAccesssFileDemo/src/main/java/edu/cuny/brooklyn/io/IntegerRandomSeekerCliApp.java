package edu.cuny.brooklyn.io;

import java.io.FileNotFoundException;
import java.io.IOException;

public class IntegerRandomSeekerCliApp {
	public static void main(String[] args) {
		if (args.length < 2) {
			System.out.println("Usage: RandomAccessFileDemo <file_name> <n-th-long-integer>");
			return;
		}
		
		try {
			LongIntegerFileSeeker seeker = new LongIntegerFileSeeker(args[0]);
			long number = seeker.readIntegerFile("files/intlist.bin", Integer.parseInt(args[1]));
			System.out.format("The number #%d is %d.%n", Integer.parseInt(args[1]), number);
		} catch (FileNotFoundException e) {
			System.err.println("Cannot find files/intlist.bin.");
		} catch (NumberFormatException e) {
			System.err.format("Expect an integer on the Command Line, but %s is not an integer.", args[0]);
		} catch (IOException e) {
			System.err.println("File to read files/intlist.bin.");
		}
	}


}
