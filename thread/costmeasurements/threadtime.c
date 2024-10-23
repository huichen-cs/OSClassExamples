#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "util.h"

void *threadFunc(void *arg) {
  (void)arg;
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t tid;
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

    if (pthread_create(&tid, NULL, threadFunc, NULL) != 0) {
      errorExit("pthread_create");
    }

    t1 = get_ns_time();

    duration = t1 - t0;
    // printf("duration = %ld\n", duration);

    total += duration;

    usleep(800);

    if (pthread_join(tid, NULL)) {
      errorExit("pthread_join");
    }
  }

  printf("average time: %f\n", (double)total / (double)count);
  exit(EXIT_SUCCESS);
}
