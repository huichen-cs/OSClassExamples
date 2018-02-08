/*
 * Copied from 
 * 	http://www.tldp.org/HOWTO/text/IO-Port-Programming
 * example.c: very simple example of port I/O
 *
 * This code does nothing useful, just a port write, a pause,
 * and a port read. Compile with `gcc -O2 -o ioportex ioportex.c',
 * and run as root with `./ioportex'.
 *
 * gcc -S ioportex.s ioportex.c 
 * 
 * x86 instruction set
 * http://www.fermimn.gov.it/linux/quarta/x86/out.htm
 * https://pdos.csail.mit.edu/6.828/2010/readings/i386/OUT.htm
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define BASEPORT 0x378 /* lp1 */

int main()
{
	/* Get access to the ports */
	if (ioperm(BASEPORT, 3, 1)) {perror("ioperm"); exit(1);}

	/* Set the data signals (D0-7) of the port to all low (0) */
	outb(0, BASEPORT);

	/* Sleep for a while (100 ms) */
	usleep(100000);

	/* Read from the status port (BASE+1) and display the result */
	printf("status: %d\n", inb(BASEPORT + 1));

	/* We don't need the ports anymore */
	if (ioperm(BASEPORT, 3, 0)) {perror("ioperm"); exit(1);}

	exit(0);
}

/* end of example.c */

