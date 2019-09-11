#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include "workfifo.h"

int main(int argc, char *argv[]) {
    pid_t pid, wpid;
    long long *maxiter, accepted, trials = 0, totalaccepted =  0;
    int *seedx, *seedy, fifofd, status, nprocesses, i;
    char maxiterbuf[128], seedxbuf[128], seedybuf[128], *piworkfifo = PI_WORK_FIFO;
    double pi;


    if (argc > 1) {
        sscanf(argv[1], "%d", &nprocesses);
    } else {
        printf("Usage: %s <NUMBER_OF_PROCESSES> <P1_MAX_ITERS> <P1_SEED_X> <P1_SEED_Y> <...>\n"
                , argv[0]);
        exit(EXIT_SUCCESS);
    }

    if (argc < nprocesses*3+2) {
        printf("Usage: %s <NUMBER_OF_PROCESSES> <P1_MAX_ITERS> <P1_SEED_X> <P1_SEED_Y> <...>\n"
                , argv[0]);
        exit(EXIT_SUCCESS);
    }

    maxiter = (long long*)malloc(sizeof(long long)*nprocesses);
    seedx = (int *)malloc(sizeof(int)*nprocesses);
    seedy = (int *)malloc(sizeof(int)*nprocesses);
    if (maxiter == NULL || seedx == NULL || seedy == NULL) {
        fprintf(stderr, "cannot allocate memory");
        exit(EXIT_FAILURE);
    }

    for (i=0; i<nprocesses; i++) {
        sscanf(argv[2+3*i], "%lld", maxiter+i); 
        sscanf(argv[2+3*i+1], "%d", seedx+i);
        sscanf(argv[2+3*i+2], "%d", seedy+i);
    }

    for (i=0; i<nprocesses; i++) {
        printf("Read from the command line for process(%d): %lld %d %d\n", i, maxiter[i]
                , seedx[i], seedy[i]);
    }

    printf("Parent starts at: PID=%d\n", getpid());


    if (mkfifo(piworkfifo, S_IRUSR | S_IWUSR) == -1) {
        perror("mkdifo error");
        exit(EXIT_FAILURE);
    }

    fifofd = open(piworkfifo, O_RDWR);
    if (fifofd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* fork a child process. see manual: man 2 fork */
    for (i=0; i<nprocesses; i++) {
        pid = fork();

        if (-1 == pid) { /* error */
            perror("fork()");
            exit(1);
        } else if (pid == 0) { /* child */
            printf("Child is forked at: PID=%d\n", getpid());
            snprintf(maxiterbuf, sizeof(maxiterbuf), "%lld", maxiter[i]);
            snprintf(seedxbuf, sizeof(seedxbuf), "%d", seedx[i]);
            snprintf(seedybuf, sizeof(seedybuf), "%d", seedy[i]);
            printf("\trun worker %d as worker %s %s %s\n", i, maxiterbuf, seedxbuf, seedybuf);
            execlp("./worker", "worker", maxiterbuf, seedxbuf, seedybuf, NULL); 
        } 
    }

    while ((wpid = wait(&status)) > 0); /* block parent */


    for (i=0; i<nprocesses; i++) {
        trials += maxiter[i];
        read(fifofd, &accepted, sizeof(long long));
        printf("accepted = %lld\n", accepted);
        totalaccepted += accepted;
    }
    printf("max trials = %lld total accepted = %lld\n", trials, totalaccepted);
    pi = (double)totalaccepted / (double)trials * 4.0;
    printf("In parent: estimated pi = %lf\n", pi);


    close(fifofd);
    unlink(piworkfifo);

    free(maxiter);
    free(seedx);
    free(seedy);
    return 0;
}
