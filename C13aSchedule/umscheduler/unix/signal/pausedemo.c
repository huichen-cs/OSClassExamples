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


    for (int i=0; i<100; i++) {
        printf("i = %d\n", i);
        alarm(3);
        pause();
    }

    return 0;
}

void alarmhandler (int signal) { 
    printf ("An alarm clock signal was received\n");
}
