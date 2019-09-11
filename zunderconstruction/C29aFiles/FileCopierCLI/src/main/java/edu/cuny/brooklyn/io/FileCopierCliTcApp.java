package edu.cuny.brooklyn.io;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FileCopierCliTcApp {
	private final static Logger LOGGER = LoggerFactory.getLogger(FileCopierCliTcApp.class);

	public static void main(String[] args) {

		FileInputStream in = null;
		FileOutputStream out = null;

		// System.out.println("Working Directory = " + System.getProperty("user.dir"));
		if (args.length < 2) {
			System.out.println("Usage: FileCopierCliTcApp <source_file> <destination_file>");
			System.exit(1);
		}

		String inputFilename = args[0];
		String outputFilename = args[1];
		try {
			in = new FileInputStream(inputFilename);
			out = new FileOutputStream(outputFilename);
			LOGGER.debug("File intput and output streams opened.");
			
			long numBytesCopied = 0l;
			int c;
			while ((c = in.read()) != -1) {
				out.write(c);
				numBytesCopied ++;
			}
			System.out.println(numBytesCopied + " bytes copied from " + inputFilename + " to " + outputFilename);
			LOGGER.debug(numBytesCopied + " bytes copied from " + inputFilename + " to " + outputFilename);
		} catch (FileNotFoundException e) {
			System.out.println("Cannot open least one of the two files: " + inputFilename + " and " + outputFilename);
		} catch (IOException e) {
			LOGGER.error("Failed to copy file", e);
			System.out.println("Failed to copy file");
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e) {
					LOGGER.error("Failed to close file", e);
					System.out.println("Failed to close the file input stream.");
				}
			}
			if (out != null) {
				try {
					out.close();
				} catch (IOException e) {
					LOGGER.error("Failed to close file", e);
					System.out.println("Failed to close the file output stream.");
				}
			}
			LOGGER.debug("Input and output streams closed.");
		}
	}
}
