#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "workfifo.h"

static double estimatepi(int fifofd, long long maxiters, unsigned int, unsigned int);

int main(int argc, char* argv[]) {
    long long maxiter = 10000000;
    unsigned int xseed = 12345;
    unsigned int yseed = 54321;
    int fifofd;
    char *piworkfifo = PI_WORK_FIFO;
    double pi;

    if (argc > 3) {
        sscanf(argv[1], "%lld", &maxiter);
        sscanf(argv[2], "%d", &xseed);
        sscanf(argv[3], "%d", &yseed);
    }
    printf("\tworker at %d: maxiter = %lld xseed = %d yseed = %d\n" , getpid(), maxiter, 
            xseed, yseed);


    fifofd = open(piworkfifo, O_RDWR);
    if (fifofd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    pi = estimatepi(fifofd, maxiter, xseed, yseed);

    printf("\tworker at pid=%d: pi = %lf\n", getpid(), pi);

    
    close(fifofd);
}

static double estimatepi(int fifofd, long long maxiters , unsigned int xseed, unsigned yseed) {
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

    printf("\tworker at pid=%d: accepted = %lld\n", getpid(), accepted);

    if (write(fifofd, &accepted, sizeof(long long)) == -1) {
        perror("\twrite");
        exit(EXIT_FAILURE);
    }

    return (double)accepted / (double)maxiters * 4.;
}

