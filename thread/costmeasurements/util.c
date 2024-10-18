#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

unsigned long long get_ns_time() {
  struct timespec ts;

  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    errorExit("clock_gettime()");
  }

  return (unsigned long long)ts.tv_sec * 1000000000llu +
         (unsigned long long)ts.tv_nsec;
}

volatile char *buf;

void allocateAndUseBuf(int mb) {

  buf = malloc(mb * 1024 * 1024);

  if (buf == NULL) {
    errorExit("malloc()");
  }

  for (int i = 0; i < mb * 1024 * 1024; i++) { // Q2. why "buf[i] = ..."?
    buf[i] = i % 255;
  }
}

void errorExit(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}
