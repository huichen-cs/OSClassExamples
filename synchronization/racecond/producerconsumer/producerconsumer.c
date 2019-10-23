#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "buffer.h"

const char *shname = "boundedbuffer";
static int initbuffer();
static void producer();
static void consumer();


int main(int argc, char *argv[]) {
    pid_t workers[2];
    int ischild = 0, childno = 0, wstatus;

    printf("In parent (pid = %d)\n", getpid());

    for (int i=0; i<2 && !ischild; i++) {
        workers[i] = fork();
        if (-1 == workers[i]) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        childno ++;
        if (workers[i] == 0) ischild = 1;
    }

    if (!ischild) {
        initbuffer();
    } else if (ischild) {
        printf("In child %d (pid = %d)\n", childno, getpid());
        switch (childno) {
            case 1: 
                producer();
                break;
            case 2:
                consumer();
                break;
        }
        printf("Leaving child %d (pid = %d)\n", childno, getpid());
        exit(EXIT_SUCCESS); 
    }


    for (int i=0; i<2; i++) {
        waitpid(workers[i], &wstatus, 0);
    }

    if (!ischild) {
        shm_unlink(shname);        
    }

    printf("Leaving parent (pid = %d)\n", getpid());
    exit(EXIT_SUCCESS);
}

static int initbuffer() {
    int fd, rtn;
    sharedbuffer_t *bufptr;

    fd = shm_open(shname, O_CREAT | O_RDWR, 0666);
    if (-1 == fd) {
        perror("shm_open");
        return -1;
    }

    rtn = ftruncate(fd, sizeof(sharedbuffer_t));
    if (-1 == rtn) {
        perror("ftruncate");
        return -1;
    }

    bufptr = (sharedbuffer_t *)mmap(0, sizeof(sharedbuffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((sharedbuffer_t *)-1 == bufptr) {
        perror("mmap");
        return -1;
    }



    bufptr->counter = 0;
    bufptr->in = 0;
    bufptr->out = 0;

    return 0;
}

static void producer() {
    int i, fd;
    sharedbuffer_t *bufptr;

    fd = shm_open(shname, O_CREAT | O_RDWR, 0666);
    if (-1 == fd) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    

    bufptr = (sharedbuffer_t *)mmap(0, sizeof(sharedbuffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((sharedbuffer_t *)-1 == bufptr) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }


    for (i=0; i<NUM_PRODUCED; i++) {
        /* produce an item in next produced */ 
        int nextproduced = i;
    
        while (bufptr->counter == BUFFER_SIZE)  
            ; /* do nothing (busy waiting) */ 
        bufptr->buffer[bufptr->in] = nextproduced; 
        bufptr->in = (bufptr->in + 1) % BUFFER_SIZE; 
        bufptr->counter ++; 
        printf("In process(%d): counter = %d\n", getpid(), bufptr->counter);
    }
}

static void consumer() {
    int i, fd, rtn, nextconsumed, sum;
    sharedbuffer_t *bufptr;

    fd = shm_open(shname, O_CREAT | O_RDWR, 0666);
    if (-1 == fd) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    rtn = ftruncate(fd, sizeof(sharedbuffer_t));
    if (-1 == rtn) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    bufptr = (sharedbuffer_t *)mmap(0, sizeof(sharedbuffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((sharedbuffer_t *)-1 == bufptr) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sum = 0; 
    for (i=0; i<NUM_PRODUCED; i++) {
        while (bufptr->counter == 0)
            ; /* do nothing */
        nextconsumed = bufptr->buffer[bufptr->out];
        bufptr->out = (bufptr->out + 1) % BUFFER_SIZE;
        bufptr->counter --;
        printf("In process(%d): counter = %d\n", getpid(), bufptr->counter);
        /* consume the item in next consumed */
        sum += nextconsumed; 
    }

    printf("The sum is %d\n", sum);
}
