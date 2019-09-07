#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    long maxiter = 10000000;
    char maxiterbuf[128];

    
    if (argc > 1) {
        sscanf(argv[1], "%ld", &maxiter);
    }
    snprintf(maxiterbuf, sizeof(maxiterbuf), "%ld", maxiter);
    printf("Parent starts at: PID=%d\n", getpid());

    /* fork a child process. see manual: man 2 fork */
    pid = fork();

    if (-1 == pid) { /* error occurred */
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { /* child process */
        printf("Child is forked at: PID=%d\n", getpid());
        execlp("./worker", "worker", maxiterbuf, "11111", "99999", NULL); 
    } else { /* parent */
        /* block parent, i.e., the parent will wait for the child to complete
	 * (or is suspended until the child completes)  */
        wait(NULL);
        printf("Child completes, and parent is to exit\n");
    }

    return 0;
}
