#include <stdio.h>
#include <stdlib.h>

static double estimatepi(long maxiters, unsigned int);

int main(int argc, char* argv[]) {
    long maxiter = 10000000;
    unsigned int seed = 12345;

    if (argc > 2) {
        sscanf(argv[1], "%ld", &maxiter);
        sscanf(argv[2], "%d", &seed);
    }
    printf("worker: maxiter = %ld seed = %d\n"
            , maxiter, seed);
    printf("worker: pi = %lf\n", estimatepi(10000000, 12345));
}

static double estimatepi(long maxiters, unsigned int seed) {
    /* 
     * A simple Monte Carlo method: 
     *
     * Consider a square of the unit length that bounds a 
     * circle of the unit diameter within, randomly generate
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
    long iter;
    long accepted = 0;


    /*
     * The choice of random number generation process
     * is poor. The process of generating x and
     * that y should be two independent processes;
     * unfortunately, the following isn't. 
     */
    srand(seed);
    for (iter=0; iter<maxiters; iter++) {
        x = (double)rand() / ((double)(RAND_MAX) + 1.); 
        y = (double)rand() / ((double)(RAND_MAX) + 1.);

        if (x*x + y*y < 1.0) {
            accepted ++;
        }
    }

    return (double)accepted / (double)maxiters * 4.;
}

