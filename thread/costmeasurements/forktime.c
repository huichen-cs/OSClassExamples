#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "util.h"

int main(int argc, char *argv[]) {
  pid_t pid;
  int count;
  int size;
  uint64_t t0, t1, duration, total = 0LLU;

  if (argc < 3) {
    printf("Usage: %s COUNT ARRAY_SIZE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  count = atoi(argv[1]);
  size = atoi(argv[2]);

  allocateAndUseBuf(size);

  for (int i = 0; i < count; i++) {
    t0 = get_ns_time();

    pid = fork();

    if (pid == 0) {
      exit(EXIT_SUCCESS);
    }

    t1 = get_ns_time();
    duration = t1 - t0;

    // printf("duration = %lld\n", duration);
    total += duration;

    usleep(800);

    if (waitpid(pid, NULL, 0) == -1) {
      errorExit("wait()");
    }
  }
  printf("average time: %f\n", (double)total / (double)count);

  exit(EXIT_SUCCESS);
}
