#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


void abort_handler(int signum);

int main() {
    int status;

     struct sigaction new_action;
    /* Set up the structure to specify the new action. */
    new_action.sa_handler = abort_handler;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(SIGABRT, &new_action, NULL);

    pid_t pid = fork();
    if (pid == 0) { /* in child */
        printf("In Child process (pid=%d)\n", getpid());
        printf("In Child process (pid=%d): child is sleeping for 15 seconds\n",
                getpid());
        sleep(15);
        printf("In Child process (pid=%d): child is exiting with code 123\n",
                getpid());
        // abort();
    } if (pid > 0) { /* in paranet */
        printf("In Parent process (pid=%d)\n", getpid());
        wait(&status);
        if (!WIFEXITED(status)) {
            printf("In Parent process (pid=%d): child exited abnormally\n",
                getpid());
        } 
        printf("In Parent process (pid=%d): child returned status %d\n",
                getpid(), WEXITSTATUS(status));
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}



void abort_handler(int signum) {
    printf("Process %d got signal %d, indicating child aborted\n", getpid(), signum);
}
