#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void exitcalled() { fprintf(stderr, "Called at exit.\n"); }

int main() {
  int fd;

  atexit(exitcalled);

  fd = open("NonExistingFile.txt", O_RDONLY);
  if (-1 == fd) {
    perror("NonExistingFile.txt");
    exit(EXIT_FAILURE);
  }

  close(fd);

  return 0;
}
