#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_rng.h>

#include "worker.h"
extern struct thread_info *tinfo;

static long long estimatepi(long long maxiters, gsl_rng *rngx,
                            gsl_rng *rngy);

void *piworker(void *param) {
    int tnum = *(int *)param;
    double *pi;
    long long accepted;
    long long maxiter = tinfo[tnum].maxiter;
    int seedx = tinfo[tnum].seedx;
    int seedy = tinfo[tnum].seedy;
    gsl_rng *rngx = tinfo[tnum].rngx;
    gsl_rng *rngy = tinfo[tnum].rngy;

    printf("\tthread at pid = %ld and tid = %lu with appid = %d\n"
           "\tmaxiter = %lld seedx = %d seedy = %d\n",
           (long)getpid(), (long)tinfo[tnum].thread_id, tinfo[tnum].thread_num, 
           maxiter, seedx, seedy);

    accepted = estimatepi(maxiter, rngx, rngy);
    tinfo[tnum].accepted = accepted;

    pi = malloc(sizeof(double));
    *pi = (double)accepted / (double)maxiter;
    return pi;
}


static long long estimatepi(long long maxiters, gsl_rng *rngx, 
                            gsl_rng *rngy) {
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
    long long iter;
    long long accepted = 0;

    double pi;

    for (iter=0; iter<maxiters; iter++) {
        x = gsl_rng_uniform(rngx);
        y = gsl_rng_uniform(rngy);

        if (x*x + y*y < 1.0) {
            accepted ++;
        }
    }

    pi = (double)accepted / (double)maxiters * 4.0;
    printf("\tworker at pid=%ld: accepted = %lld pi = %lf\n", (long)getpid(), 
           accepted, pi);

    return accepted;
}

