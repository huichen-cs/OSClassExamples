#define _GNU_SOURCE
#include <linux/sched.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>


const int STACK_SIZE = 1 << 21; // 2 MB

int state = 0;

int change_print_var(void *pt) {
  int old_state = state;
  state = -1;
  printf("Child[pid=%d]: change_print_var: change state from %d to %d\n", getpid(), old_state, state);
  return 0;
}

int main(int argc, char *argv[])
{
  int wstatus, w;
  char *stack = malloc(STACK_SIZE);
  if (stack == NULL) {
    perror("malloc");
    exit(1);
  }

  char *stack_top = stack + STACK_SIZE;

  pid_t pid;
  struct clone_args args = {0};

  printf("Parent[pid=%d]: state initialized to %d\n", getpid(), state);

  pid = clone(change_print_var, stack_top, CLONE_VM | SIGCHLD, NULL);
  if (pid == -1) {
    perror("syscall(SYS_clone3 ...");
    exit(1);
  } else {
    printf("Parent[pid = %d]: clone returned %d\n", getpid(), pid);
    // sleep(1);
    // wait for the child to exit
    while ((w = waitpid(pid, &wstatus, 0)) > 0);
    printf("Parent[pid = %d]: after child exited: state = %d\n", getpid(), state);
  }

  return 0;
}

