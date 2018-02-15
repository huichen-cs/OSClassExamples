#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent starts at: PID=%d\n", getpid());

    /* fork a child process. see manual: man 2 fork */
    pid = fork();

    if (-1 == pid) { /* error */
        perror("fork()");
        exit(1);
    } else if (pid == 0) { /* child */
        printf("Child is forked at: PID=%d\n", getpid());
        execlp("./worker", "workder", "10000000", "11111", "99999", NULL); 
    } else { /* parent */
        /* block parent */
        wait(NULL);
        printf("Child completes, and parent exists\n");
    }

    return 0;
}
