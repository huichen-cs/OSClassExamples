#define _GNU_SOURCE
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "util.h"

const int STACK_SIZE = 1024 * 1024;

int dummy(void *arg) { exit(EXIT_SUCCESS); }

int main(int argc, char *argv[]) {
  char *stack = malloc(STACK_SIZE);
  char *stackTop = stack + STACK_SIZE;
  pid_t pid;
  int count;
  int size;
  uint64_t t0, t1, total = 0LLU;

  if (argc < 3) {
    printf("Usage: %s COUNT ARRAY_SIZE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  count = atoi(argv[1]);
  size = atoi(argv[2]);

  allocateAndUseBuf(size);

  t0 = get_ns_time();
  for (int i = 0; i < count; i++) {
    pid = clone(dummy, stackTop, SIGCHLD, NULL);
    if (pid == -1) {
      perror("clone");
    }
  }
  t1 = get_ns_time();
  total = t1 - t0;
  printf("average time: %f\n", (double)total / (double)count);

  exit(EXIT_SUCCESS);
}
