#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void alarmhandler(int signal);

static const long TIME_TO_SLEEP_IN_NS = 100000000;;

int main(int argc, char ** argv) {
    pid_t pid;

    if (argc < 2) {
        pid = getpid();

        struct sigaction sigact;

        sigact.sa_handler = alarmhandler;
        sigemptyset(&sigact.sa_mask);
        sigact.sa_flags = 0;
        sigaction(SIGALRM, &sigact, NULL);
    } else {
        sscanf(argv[1], "%d", &pid);
    }


    struct timespec interval;
    interval.tv_sec = 0;
    interval.tv_nsec = TIME_TO_SLEEP_IN_NS;


    while (1) {
        nanosleep(&interval, NULL);
        if (-1 == kill(pid, SIGALRM)) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

static void alarmhandler(int signal) {
    printf("Timer fired\n");
}
