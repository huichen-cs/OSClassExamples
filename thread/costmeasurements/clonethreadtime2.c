#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "util.h"

const int STACK_SIZE = 1024*1024;

int dummy(void *arg) {
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    char **stack; 
    char **stackTop; 
    pid_t pid;
    int count;
    int size;
    unsigned long long t0, t1, total = 0LLU;

    if (argc < 3) {
        printf("Usage: %s COUNT ARRAY_SIZE\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    count = atoi(argv[1]);
    size = atoi(argv[2]); 

    stack = malloc(count*sizeof(char*));
    stackTop = malloc(count*sizeof(char*));
    for (int i=0; i<count; i++) {
        stack[i] = malloc(STACK_SIZE);
        stackTop[i] = stack[i] + STACK_SIZE;
    }

    allocateAndUseBuf(size);

    t0 = get_ns_time();
    for (int i=0; i<count; i++) {
        pid = clone(dummy, stackTop[i], CLONE_VM | SIGCHLD, NULL);
        if (pid == -1) {
            perror("clone(...CLONE_VM...)");
        }
    }
    t1 =  get_ns_time();
    total = t1 - t0;
    printf("average time: %f\n", (double)total/(double)count);

    for (int i=0; i<count; i++) {
        free(stack[i]);
    }
    free(stackTop);
    free(stack);
    exit(EXIT_SUCCESS);
}
