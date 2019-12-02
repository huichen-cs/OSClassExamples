#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char c;
	int fd;

	fd = open("/dev/chardev", O_RDWR);
	if (fd == -1) {
		perror("open /dev/chardev");
		exit(EXIT_FAILURE);
	}

	printf("Attempt to read /dev/chardev\n");
	while (read(fd, &c, sizeof(c)) > 0) {
		printf("Read %c\n", c);
	}

	printf("Attempt to write /dev/chardev\n");
	c = 'H';
	if (write(fd, &c, sizeof(c)) == -1) {
		fprintf(stderr, 
			"Attempted to write to /dev/chardev: "
			"Error no %d(%s)\n"
			"Attempted to write to /dev/chardev: "
			"Error msg %s\n", 
			EINVAL, errno == EINVAL?"EINVAL":"Not EINVAL",
			strerror(errno)); 
	}

	close(fd);
	exit(EXIT_SUCCESS);	
}
