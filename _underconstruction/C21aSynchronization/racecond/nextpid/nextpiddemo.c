#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* static void printpid(); */
static int *inittid();
static void destroytid();
static int next_avail_tid();

#define NEXTTIDMEM "nexttidmem"
static int nexttid;
static int* tidptr;

int main(int argc, char *argv[]) {
    int ischild = 0, nchildren = 4, localtid;
    pid_t pid, *childpids;

    printf("parent[pid=%d] created\n", getpid());

    if (argc > 1) {
        sscanf(argv[1], "%d", &nchildren);
    }

    childpids = (pid_t *)malloc(nchildren*sizeof(pid_t));
    if (NULL == childpids) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    tidptr = inittid();
    if (NULL == tidptr) {
        fprintf(stderr, "Failed to inittid()\n");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<nchildren && !ischild; i++) {
        pid = fork();
        if (-1 == pid) {
            perror("fork()");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            ischild = 1;
        } else {
            printf("child[pid=%d] created\n", pid);
            childpids[i] = pid;
        }
    }

    if (ischild) {
        /* printpid(); */
        tidptr = inittid();
        if (NULL == tidptr) {
            fprintf(stderr, "Failed to inittid()\n");
            exit(EXIT_FAILURE);
        }
        localtid = next_avail_tid();
        printf("local tid: %d\n", localtid);
        
    } else {
        for (int i=0; i<nchildren; i++) {
            waitpid(childpids[i], NULL, 0);
        }
        destroytid();
    }

    free(childpids);
    return EXIT_SUCCESS;
}

/*
static void printpid() {
    printf("In child[pid=%d]\n", getpid());
}
*/

static int next_avail_tid() { 
    return ++(* tidptr);
}

static int *inittid() {
    int fd, rtn, *pidptr;
    fd  = shm_open(NEXTTIDMEM, O_CREAT | O_RDWR, 0666);
    if (-1 == fd) {
        perror("shm_open");
        return NULL;
    }

    rtn = ftruncate(fd, sizeof(int)); 
    if (-1 == rtn) {
        perror("ftruncate");
        return NULL;
    }

    pidptr = (int *)mmap(&nexttid, sizeof(nexttid), PROT_READ | PROT_WRITE, 
                  MAP_SHARED, fd, 0);
    if ((int *)-1 == pidptr) {
        perror("mmap");
        return NULL;
    }

    return pidptr;
}

static void destroytid() {
    shm_unlink(NEXTTIDMEM);
}
