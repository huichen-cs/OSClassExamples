#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sighandler(int signum);

int main() {
    int *ptr = 0;

    signal(SIGSEGV, sighandler);

    printf("attempt to assign 12345 to *ptr=%p\n", ptr); 
    *ptr = 12345;

    return 0;
}

void sighandler(int signum) {
    printf("Process %d got signal %d, and must exit.\n", getpid(), signum);
    exit(EXIT_FAILURE);
}
