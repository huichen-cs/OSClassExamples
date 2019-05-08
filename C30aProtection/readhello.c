#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fid, bytesread;
	char msg[128];

	printf("user (%d) executes the process as user (%d)\n", 
			getuid(), geteuid());

	fid = open("hello.txt", O_RDONLY);
	if (fid == -1) {
		perror("open");
		exit(1);
	}
	printf("opened hello.txt\n");
	bytesread = read(fid, msg, 16);
	if (-1 == bytesread) {
		perror("write");
		exit(1);
	}
	close(fid);
	msg[bytesread] = '\0';
	printf("Read \"%s\" from hello.txt\n", msg);

	return 0;
}
