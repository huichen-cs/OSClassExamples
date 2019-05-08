#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fid;
	char msg[] = "Hello, World!";

	printf("user (%d) executes the process as user (%d)\n", 
			getuid(), geteuid());

	fid = open("hello.txt", O_WRONLY|O_CREAT, 0646);
	if (fid == -1) {
		perror("open");
		exit(1);
	}
	printf("opened hello.txt\n");
	if (-1 == write(fid, msg, sizeof(msg))) {
		perror("write");
		exit(1);
	}
	close(fid);
	printf("wrote \"%s\" to hello.txt\n", msg);

	return 0;
}
