#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "util.h"

void *threadFunc(void *arg) { return EXIT_SUCCESS; }

int main(int argc, char *argv[]) {
  pthread_t tid;
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
    if (pthread_create(&tid, NULL, threadFunc, NULL) != 0) {
      errorExit("pthread_create");
    }
  }
  t1 = get_ns_time();
  total = t1 - t0;
  printf("average time: %f\n", (double)total / (double)count);
  exit(EXIT_SUCCESS);
}
