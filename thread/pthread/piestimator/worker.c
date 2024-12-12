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

  printf("\tthread at pid = %d and tid = %lu with appid = %d\n"
         "\tmaxiter = %" PRId64 " seedx = %d seedy = %d\n",
         getpid(), tinfo[tnum].thread_id, tinfo[tnum].thread_num, maxiter,
         seedx, seedy);

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

  struct random_data xbuf = {.state = NULL};
  struct random_data ybuf = {.state = NULL};
  char xstate[256];
  char ystate[256];

  double pi;

  initstate_r(xseed, xstate, sizeof(xstate), &xbuf);
  initstate_r(yseed, ystate, sizeof(ystate), &ybuf);
  for (iter = 0; iter < maxiters; iter++) {
    int32_t rn;

    setstate_r(xstate, &xbuf);
    random_r(&xbuf, &rn);
    x = ((double)rn) / ((double)(RAND_MAX) + 1.);

    setstate_r(ystate, &ybuf);
    random_r(&ybuf, &rn);
    y = ((double)rn) / ((double)(RAND_MAX) + 1.);

    if (x * x + y * y < 1.0) {
      accepted++;
    }
  }

  pi = (double)accepted / (double)maxiters * 4.0;
  printf("\tworker at pid=%d: accepted = %" PRId64 " pi = %lf\n", getpid(),
         accepted, pi);

  return accepted;
}
