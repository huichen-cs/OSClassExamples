#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "buffer.h"

const char *shname = "boundedbuffer";
static sharedbuffer_t *initbuffer();
static void closebuffer(sharedbuffer_t *bufptr);
static void producer();
static void consumer();


int main(int argc, char *argv[]) {
    pid_t workers[2];
    int ischild = 0, childno = 0, wstatus;
    sharedbuffer_t *bufptr = NULL;

    printf("In parent (pid = %d)\n", getpid());

    bufptr = initbuffer();
    if (NULL == bufptr) {
        fprintf(stderr, "Failed to initbuffer()\n");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<2 && !ischild; i++) {
        workers[i] = fork();
        if (-1 == workers[i]) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        childno ++;
        if (workers[i] == 0) ischild = 1;
    }

    if (ischild) {
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
        closebuffer(bufptr);
    }

    printf("Leaving parent (pid = %d)\n", getpid());
    exit(EXIT_SUCCESS);
}

static sharedbuffer_t *initbuffer() {
    int fd, rtn;
    sharedbuffer_t *bufptr;

    fd = shm_open(shname, O_CREAT | O_RDWR, 0666);
    if (-1 == fd) {
        perror("shm_open");
        return NULL;
    }

    rtn = ftruncate(fd, sizeof(sharedbuffer_t));
    if (-1 == rtn) {
        perror("ftruncate");
        return NULL;
    }

    bufptr = (sharedbuffer_t *)mmap(0, sizeof(sharedbuffer_t), 
                                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((sharedbuffer_t *)-1 == bufptr) {
        perror("mmap");
        return NULL;
    }

    bufptr->in = 0;
    bufptr->out = 0;

    rtn = sem_init(&bufptr->mutex, 1, 1);
    if (-1 == rtn) {
        perror("sem_init");
        return NULL;
    }

    rtn = sem_init(&bufptr->empty, 1, BUFFER_SIZE);
    if (-1 == rtn) {
        perror("sem_init");
        return NULL;
    }

    rtn = sem_init(&bufptr->full, 1, 0);
    if (-1 == rtn) {
        perror("sem_init");
        return NULL;
    }


    return bufptr;
}

static void closebuffer(sharedbuffer_t *bufptr) {
    if (NULL != bufptr) {
        sem_destroy(&bufptr->mutex);
        sem_destroy(&bufptr->empty);
        sem_destroy(&bufptr->full);
    }
    shm_unlink(shname);        
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

        sem_wait(&bufptr->empty);
        sem_wait(&bufptr->mutex);
    
        bufptr->buffer[bufptr->in] = nextproduced; 
        bufptr->in = (bufptr->in + 1) % BUFFER_SIZE; 

        int mutex, empty, full;
        sem_getvalue(&bufptr->mutex, &mutex);
        sem_getvalue(&bufptr->empty, &empty),
        sem_getvalue(&bufptr->full, &full);
        printf("In process(%d): (i, mutex, empty, full) = (%d, %d, %d, %d)\n", 
                getpid(), i, mutex, empty, full);

        sem_post(&bufptr->mutex);
        sem_post(&bufptr->full);
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

    bufptr = (sharedbuffer_t *)mmap(0, sizeof(sharedbuffer_t), 
                                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if ((sharedbuffer_t *)-1 == bufptr) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sum = 0; 
    for (i=0; i<NUM_PRODUCED; i++) {
        sem_wait(&bufptr->full);
        sem_wait(&bufptr->mutex);

        nextconsumed = bufptr->buffer[bufptr->out];
        bufptr->out = (bufptr->out + 1) % BUFFER_SIZE;

        int mutex, empty, full;
        sem_getvalue(&bufptr->mutex, &mutex);
        sem_getvalue(&bufptr->empty, &empty),
        sem_getvalue(&bufptr->full, &full);
        printf("In process(%d): (i, mutex, empty, full) = (%d, %d, %d, %d)\n", 
                getpid(), i, mutex, empty, full);


        sem_post(&bufptr->mutex);
        sem_post(&bufptr->empty);

        /* consume the item in next consumed */
        sum += nextconsumed; 
    }

    printf("The sum is %d\n", sum);
}
