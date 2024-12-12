#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "worker.h"
extern struct thread_info *tinfo;

static int64_t estimatepi(int64_t maxiters, unsigned int xseed, unsigned yseed);

void *piworker(void *param) {
  int tnum = *(int *)param;
  double *pi;
  int64_t accepted;
  int64_t maxiter = tinfo[tnum].maxiter;
  int seedx = tinfo[tnum].seedx;
  int seedy = tinfo[tnum].seedy;

  printf("\tthread at pid = %d and tid = %lu with appid = %d\n", getpid(),
         tinfo[tnum].thread_id, tinfo[tnum].thread_num);

  accepted = estimatepi(maxiter, seedx, seedy);
  tinfo[tnum].accepted = accepted;

  pi = malloc(sizeof(double));
  *pi = (double)accepted / (double)maxiter;
  return pi;
}

static int64_t estimatepi(int64_t maxiters, unsigned int xseed,
                          unsigned yseed) {
  /*
   * A simple Monte Carlo method:
   *
   * Consider a square of the unit length that bounds a
   * circle of the unit diameter, randomly generate
   * a point in the square, if it is within the circle
   * accept it; otherwise reject it. The probability
   * a point is being accept is,
   *
   * P(Accepted) = {Area of Circle}/{Area of Square}
   *                         = pi * (1/2 * 1/2) / (1 * 1)
   *                         = pi / 4
   *
   * We arrive at
   *
   * Pi = 4 * P(Accepted)
   *        = 4 * {# accepted} / {total # of points}
   */

  double x;
  double y;
  int64_t iter;
  int64_t accepted = 0;

  char xstate[256];
  char ystate[256];

  double pi;

  initstate(xseed, xstate, sizeof(xstate));
  initstate(yseed, ystate, sizeof(ystate));
  for (iter = 0; iter < maxiters; iter++) {
    setstate(xstate);
    x = (double)random() / ((double)(RAND_MAX) + 1.);
    setstate(ystate);
    y = (double)random() / ((double)(RAND_MAX) + 1.);

    if (x * x + y * y < 1.0) {
      accepted++;
    }
  }

  pi = (double)accepted / (double)maxiters * 4.0;
  printf("\tworker at pid=%d: accepted = %" PRId64 " pi = %lf\n", getpid(),
         accepted, pi);

  return accepted;
}
