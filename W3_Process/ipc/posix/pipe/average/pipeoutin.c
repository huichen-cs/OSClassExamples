#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (-1 == pid) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("./gennumbers", "./gennumbers", NULL);
    } else {
        close(fd[1]);
        pid = fork();
        if (-1 == pid) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execl("./average", "./average", NULL);
        } else {
            close(fd[0]);
        } 
        wait(NULL);
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
