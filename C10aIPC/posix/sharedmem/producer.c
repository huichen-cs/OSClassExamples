/**
 * Revised based on the sample code in 
 *   Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *   concepts. Wiley, 2018.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>


int main() {

	/* the size (in bytes) of shared memory object */
	const int SIZE = 4096;

	/* name of the shared memory object */
	const char *name = "OS1";

	/* strings written to shared memory */
	const char *message_0 = "Hello";
	const char *message_1 = "World!";

	/* shared memory file descriptor */
	int fd, rtn;

	/* pointer to shared memory obect */
	char *ptr;

	/* create the shared memory object */
	fd = shm_open(name,O_CREAT | O_RDWR,0666);
	if (-1 == fd) {
		perror("shm_open");
		exit(EXIT_FAILURE);
	} 

	/* configure the size of the shared memory object */
	rtn = ftruncate(fd, SIZE);
	if (-1 == rtn) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	/* memory map the shared memory object */
	ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ((char *)-1 == ptr) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	/* write to the shared memory object */
	sprintf(ptr,"%s",message_0);
	ptr += strlen(message_0);
	sprintf(ptr,"%s",message_1);
	ptr += strlen(message_1);

	return 0;
}
