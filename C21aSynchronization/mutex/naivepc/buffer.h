#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

#define NUM_PRODUCED 10000
#define BUFFER_SIZE 4096
typedef struct sharedbuffer {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int counter;
    pthread_mutex_t countermutex;
    pthread_mutexattr_t mutexattr;
} sharedbuffer_t;

#endif
