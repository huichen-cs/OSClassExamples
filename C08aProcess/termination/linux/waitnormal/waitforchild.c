#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>



int main() {
    int status;

    pid_t pid = fork();
    if (pid == 0) { /* in child */
        printf("In Child process (pid=%d)\n", getpid());
        printf("In Child process (pid=%d): child is sleeping for 15 seconds\n",
                getpid());
        sleep(15);
        printf("In Child process (pid=%d): child is exiting with code 123\n",
                getpid());
        exit(123);
    } if (pid > 0) { /* in paranet */
        printf("In Parent process (pid=%d)\n", getpid());
        wait(&status);
        if (WIFEXITED(status)) {
            printf("In Parent process (pid=%d): child exited normally\n",
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


