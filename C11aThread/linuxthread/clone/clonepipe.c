/*
 * This example is modeled after the exxample program in the Linux manual page
 * of clone(2). 
 *
 * See  https://www.kernel.org/doc/man-pages/
 */

#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

static int              /* Start function for cloned child */
childFunc(void *arg)
{
   int msglen;

   int *pipefd = (int *)arg;
   int readfd = pipefd[0];
   int writefd = pipefd[3];

   /* read message from the pipe */
   if (read(readfd, &msglen, sizeof(msglen)) != sizeof(msglen)) errExit("c: read");
   printf("Child: message length = %d\n", msglen);

   char *msgbuf = malloc(msglen + 1);
   if (NULL == msgbuf) errExit("c: malloc");

   int nbytes = read(readfd, msgbuf, msglen);
   if (-1 == nbytes || nbytes > msglen) errExit("c: read");
   msgbuf[nbytes + 1] = '\0';
   printf("Child: message content = %s\n", msgbuf);

   /* write back the message */
   if (-1 == write(writefd, &msglen, sizeof(msglen))) errExit("c: write");
   if (-1 == write(writefd, msgbuf, nbytes)) errExit("c: write");
   printf("Child: wrote message back\n");

   sleep(5);

   free(msgbuf);
   close(pipefd[0]);
   close(pipefd[1]);
   return 0;           /* Child terminates now */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

int
main(int argc, char *argv[])
{
   char *stack;                    /* Start of stack buffer */
   char *stackTop;                 /* End of stack buffer */
   pid_t pid;
   int pipefd[4];

   if (argc < 2) {
       fprintf(stderr, "Usage: %s <message>\n", argv[0]);
       exit(EXIT_SUCCESS);
   }

   /* open an ordinary pipe */
   if (-1 == pipe(pipefd)) errExit("p: pipe"); 
   if (-1 == pipe(pipefd + 2)) errExit("p: pipe"); 

   /* Allocate stack for child */
   stack = malloc(STACK_SIZE);
   if (stack == NULL) errExit("p: malloc");
   stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

   pid = clone(childFunc, stackTop, SIGCHLD, (void *)pipefd);
   if (pid == -1) errExit("p: clone");
   printf("clone() returned %ld\n", (long) pid);

   /* Parent falls through to here */

   sleep(1); /* Give child time to change its hostname */

   int msglen = strlen(argv[1]);
   if (-1 == write(pipefd[1], &msglen, sizeof(msglen))) errExit("p: write");
   if (-1 == write(pipefd[1], argv[1], strlen(argv[1]))) errExit("p: write");

   if (read(pipefd[2], &msglen, sizeof(msglen)) != sizeof(msglen)) errExit("p: read");
   printf("P: message length = %d\n", msglen);

   char *msgbuf = malloc(msglen + 1);
   if (NULL == msgbuf) errExit("p: malloc");

   int nbytes = read(pipefd[2], msgbuf, msglen);
   if (-1 == nbytes || nbytes > msglen) errExit("p: read");
   msgbuf[nbytes + 1] = '\0';
   printf("p: message content = %s\n", msgbuf);

   if (waitpid(pid, NULL, 0) == -1) errExit("waitpid"); /* Wait for child */
   printf("child has terminated\n");

   free(msgbuf);
   close(pipefd[0]);
   close(pipefd[1]);

   exit(EXIT_SUCCESS);
}
