#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_rng.h>

#include "worker.h"
extern struct thread_info *tinfo;

static int64_t estimatepi(int64_t maxiters, gsl_rng *rngx, gsl_rng *rngy);

void *piworker(void *param) {
  int tnum = *(int *)param;
  double *pi;
  int64_t accepted;
  int64_t maxiter = tinfo[tnum].maxiter;
  int seedx = tinfo[tnum].seedx;
  int seedy = tinfo[tnum].seedy;
  gsl_rng *rngx = tinfo[tnum].rngx;
  gsl_rng *rngy = tinfo[tnum].rngy;

  printf("\tthread at pid = %" PRId32 " and tid = %" PRId32 " with appid = %d\n"
         "\tmaxiter = %" PRId64 " seedx = %d seedy = %d\n",
         (int32_t)getpid(), (int32_t)tinfo[tnum].thread_id,
         tinfo[tnum].thread_num, maxiter, seedx, seedy);

  accepted = estimatepi(maxiter, rngx, rngy);
  tinfo[tnum].accepted = accepted;

  pi = malloc(sizeof(double));
  *pi = (double)accepted / (double)maxiter;
  return pi;
}

static int64_t estimatepi(int64_t maxiters, gsl_rng *rngx, gsl_rng *rngy) {
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

  double pi;

  for (iter = 0; iter < maxiters; iter++) {
    x = gsl_rng_uniform(rngx);
    y = gsl_rng_uniform(rngy);

    if (x * x + y * y < 1.0) {
      accepted++;
    }
  }

  pi = (double)accepted / (double)maxiters * 4.0;
  printf("\tworker at pid=%" PRId32 ": accepted = %" PRId64 " pi = %lf\n",
         (int32_t)getpid(), accepted, pi);

  return accepted;
}
