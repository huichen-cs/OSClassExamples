#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include "readwrite.h"

void *readwrite(void *param) {
    struct thread_info *tinfoptr = (struct thread_info*)param;
    int *itemptr = tinfoptr->item;

    int i, stop = rand()*1000, s;

    /* do some random stuff, takes random amount of time */
    for (i=0; i<stop; i++) {
       s += i; 
    }
    s = s*s;

    printf("thread = %d item = %d\n", tinfoptr->thread_num, *itemptr);
    (*itemptr) = (*itemptr) * tinfoptr->thread_num + 1;

    return param;
}




