#ifndef BUFFER_H
#define BUFFER_H

#define NUM_PRODUCED 10000
#define BUFFER_SIZE 4096
typedef struct sharedbuffer {
  int buffer[BUFFER_SIZE];
  int in;
  int out;
  int counter;
} sharedbuffer_t;

#endif
