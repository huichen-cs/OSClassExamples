#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include "readwrite.h"

int main(int argc, char *argv[]) {
    int i, *itemptr, status, seed;
    struct thread_info *tinfo;
    pthread_attr_t attr;
    void *res;

    /* get parameters from the command line */
    if (argc > 1) {
        sscanf(argv[1], "%d", &seed);
        srand(seed);
    } else {
        srand(time(NULL));
    }

    tinfo = calloc(2, sizeof(struct thread_info));
    if (tinfo == NULL) {
        handle_error("calloc tinfo");
    }

    itemptr = calloc(1, sizeof(int));
    if (itemptr == NULL) {
        handle_error("calloc itemptr");
    }
    *itemptr = 10;


    /* create threads: multiple steps */
    /* 1. Initialize thread creation attributes */
    status = pthread_attr_init(&attr);
    if (status != 0) {
        handle_error_en(status, "pthread_attr_init");
    }


    /* 2. Create two threads */
    for (i = 0; i < 2; i++) { 
        tinfo[i].thread_num = i;
        tinfo[i].item = itemptr;
        /* The pthread_create() call stores the thread ID into corresponding element 
         * of tinfo[] */
        status = pthread_create(&tinfo[i].thread_id, &attr, &readwrite, &tinfo[i]);
        if (status != 0) {
            handle_error_en(status, "The producer thread pthread_create'd");
        }
    }

    /* Destroy the thread attributes object, since it is no longer needed */
    status = pthread_attr_destroy(&attr);
    if (status != 0) {
        handle_error_en(status, "pthread_attr_destroy");
    }

    /* Now join with each thread, and display its returned value */
    for (i = 0; i < 2; i++) {
        status = pthread_join(tinfo[i].thread_id, &res);
        if (status != 0) {
            handle_error_en(status, "Thread pthread_join'ed");
        }

        printf("Joined with thread %d; returned value was %lf\n", tinfo[i].thread_num, 
            *((double *)res));
    }

    printf("item = %d\n", *itemptr);

    free(itemptr);
    free(tinfo);
    exit(EXIT_SUCCESS);
}

