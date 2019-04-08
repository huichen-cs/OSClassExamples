#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 4
typedef struct sharedbuffer {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int counter;
} sharedbuffer_t;

#endif
