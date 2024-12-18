#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int status;
  pid_t pid = getpid();

  if (argc > 1) {
    pid = atoi(argv[1]);
  }

  printf("Process PID=%d attempts to kill process PID=%d\n", getpid(), pid);

  status = kill(pid, SIGKILL);
  if (-1 == status) {
    perror("kill");
    exit(EXIT_FAILURE);
  }

  return 0;
}
