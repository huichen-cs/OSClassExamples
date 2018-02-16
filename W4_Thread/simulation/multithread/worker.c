#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include "worker.h"

static long long estimatepi(long long maxiters , unsigned int xseed, unsigned yseed);

void *piworker(void *param) {
    struct thread_info *tinfoptr = (struct thread_info*)param;
    double *piptr;
    long long accepted;
    long long maxiter = tinfoptr->maxiter;
    int seedx = tinfoptr->seedx;
    int seedy = tinfoptr->seedy;

    printf("\tthread at pid = %d and tid = %lu with appid = %d\n"
            , getpid(), tinfoptr->thread_id, tinfoptr->thread_num);

    accepted = estimatepi(maxiter, seedx, seedy);
    tinfoptr->accepted = accepted;

    piptr = malloc(sizeof(double));
    *piptr = (double)accepted / (double)maxiter;
    return piptr;
}


static long long estimatepi(long long maxiters , unsigned int xseed, unsigned yseed) {
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

    char xstate[256];
    char ystate[256];

    double pi;

    initstate(xseed, xstate, sizeof(xstate));
    initstate(yseed, ystate, sizeof(ystate));
    for (iter=0; iter<maxiters; iter++) {
        setstate(xstate);
        x = (double)random() / ((double)(RAND_MAX) + 1.); 
        setstate(ystate);
        y = (double)random() / ((double)(RAND_MAX) + 1.);

        if (x*x + y*y < 1.0) {
            accepted ++;
        }
    }

    pi = (double)accepted / (double)maxiters;
    printf("\tworker at pid=%d: accepted = %lld pi = %lf\n", getpid(), accepted, pi);


    return accepted;
}

