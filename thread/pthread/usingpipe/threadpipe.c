#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pipefd[4];

static void *pipethread(void *arg);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <message> \n", argv[0]);
    return 0;
  }

  /* create two ordinary pipes */
  if (-1 == pipe(pipefd)) { perror("p: pipe"); exit(EXIT_FAILURE); }
  if (-1 == pipe(pipefd + 2)) { perror("p: pipe"); exit(EXIT_FAILURE); }

  pthread_t tid;  /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */

  /* set the default attributes of the thread */
  pthread_attr_init(&attr);

  /* create thread */
  pthread_create(&tid, &attr, pipethread, argv[1]);

  /* read and write to the two pipes */
  int readfd = pipefd[0];
  int writefd = pipefd[3];

  int nbytes, msglen;
  if (read(readfd, &msglen, sizeof(msglen)) != sizeof(msglen)) {
      perror("p: read msglen");
      exit(EXIT_FAILURE);
  }
  printf("p: read from pipe integer msglen %d\n", msglen);

  char *msgbuf = malloc(msglen + 1);
  if (NULL == msgbuf) { perror("p: malloc"); exit(EXIT_FAILURE); }

  nbytes = read(readfd, msgbuf, msglen);
  if (-1 == nbytes || nbytes > msglen) { 
      perror("p: read message"); exit(EXIT_FAILURE); 
  }
  msgbuf[nbytes] = '\0';
  printf("p: read from pipe message %s\n", msgbuf);

  if (-1 == write(writefd, &msglen, sizeof(msglen))) {
    perror("p: write msglen");
    exit(EXIT_FAILURE);
  }
  printf("p: wrote to pipe integer %d\n", msglen);

  if (-1 == write(writefd, msgbuf, nbytes)) {
    perror("p: write message");
    exit(EXIT_FAILURE);
  }
  printf("p: wrote to pipe message %s\n", msgbuf);

  /* wait for the thread to exit */
  pthread_join(tid, NULL);

  return 0;
}

static void *pipethread(void *arg) {
  int readfd = pipefd[2];
  int writefd = pipefd[1];

  int msglen = strlen((char *)arg);
  if (-1 == write(writefd, &msglen, sizeof(msglen))) {
    perror("c: write msglen");
    exit(EXIT_FAILURE);
  }
  printf("c: wrote to pipe integer %d\n", msglen);

  if (-1 == write(writefd, arg, msglen)) {
    perror("c: write message");
    exit(EXIT_FAILURE);
  }
  printf("c: wrote to pipe message %s\n", (char *)arg);

  if (read(readfd, &msglen, sizeof(msglen)) != sizeof(msglen)) {
    perror("p: read msglen");
    exit(EXIT_FAILURE);
  }
  printf("c: read from pipe integer %d\n", msglen);

  char *msgbuf = malloc(msglen + 1);
  if (NULL == msgbuf) { perror("c: malloc"); exit(EXIT_FAILURE); }
  int nbytes = read(readfd, msgbuf, msglen);
  if (-1 == nbytes || nbytes > msglen) { 
      perror("c: reaad msg"); exit(EXIT_FAILURE); 
  }
  msgbuf[nbytes + 1] = '\0';
  printf("c: read from pipe message %s\n", msgbuf);

  return NULL;
}

