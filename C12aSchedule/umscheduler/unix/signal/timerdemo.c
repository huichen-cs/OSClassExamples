#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarmhandler(int signal);

int main(int argc, char *argv[]) {
    struct sigaction sigact;

    memset(&sigact, 0, sizeof(sigact));
    sigact.sa_handler = alarmhandler;
    sigaction(SIGALRM, &sigact, NULL);
    alarm(1);


    for (int i=0; i<100; i++) {
        printf("i = %d\n", i);
        usleep(500000);
    }

    return 0;
}

void alarmhandler (int signal) { 
    printf ("An alarm clock signal was received\n");
}
