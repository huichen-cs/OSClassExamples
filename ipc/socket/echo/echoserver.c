#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static void print_net_msg(char *msgprefix, struct sockaddr_in *addr);
static void cleanup();
static void docleanup(int signum);

static const char *SERVER_ADDR = "0.0.0.0";
static const int SERVER_PORT = 61234;
static const int BACKLOG = 5;

static int sfd = -1, cfd = -1;

int main(int argc, char *argv[]) {
  pid_t pid;
  int ret = EXIT_SUCCESS, bytesreceived;
  socklen_t caddrlen;
  struct sockaddr_in saddr, caddr;
  struct sigaction sigact;
  char buf[128];

  printf("server starts running at process %d ...\n", getpid());

  atexit(cleanup);
  sigact.sa_handler = docleanup;
  sigaction(SIGINT, &sigact, NULL);

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == sfd) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(SERVER_PORT);
  if (0 == inet_pton(AF_INET, SERVER_ADDR, &(saddr.sin_addr.s_addr))) {
    fprintf(stderr, "%s isn't valid IP address\n", SERVER_ADDR);
    exit(EXIT_FAILURE);
  }

  if (-1 == bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr))) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (-1 == listen(sfd, BACKLOG)) {
    perror("lisen");
    exit(EXIT_FAILURE);
  }
  print_net_msg("server is listening to", &saddr);
  printf("server at process %d is ready to accept connection.\n", getpid());

  caddrlen = sizeof(struct sockaddr_in);
  while ((cfd = accept(sfd, (struct sockaddr *)&caddr, &caddrlen)) >= 0) {
    if (-1 == cfd) {
      perror("accept");
      ret = EXIT_FAILURE;
      break;
    }
    print_net_msg("server accepted connection from", &caddr);

    pid = fork();
    if (-1 == pid) {
      perror("fork");
      ret = EXIT_FAILURE;
      break;
    } else if (pid == 0) { /* child */
      printf("process %d is handling client\n", getpid());
      close(sfd);     /* not used by the child */
      pid = getpid(); /* child's pid */
      while (1) {
        bytesreceived = recv(cfd, buf, sizeof(buf) - 1, 0);
        if (-1 == bytesreceived) {
          perror("recv");
          exit(EXIT_FAILURE);
        }
        buf[bytesreceived] = '\0';
        printf("received from client at process %d: %s\n", pid, buf);
        if (-1 == send(cfd, buf, bytesreceived, MSG_NOSIGNAL)) {
          perror("send");
          exit(EXIT_FAILURE);
        }
        printf("echoed back to client at process %d: %s\n", pid, buf);
        if (strncasecmp(buf, "Bye!", 4) == 0) {
          break;
        }
      }
      printf("client said 'Bye!', and process %d exiting ...\n", pid);
      exit(EXIT_SUCCESS);
    }
    printf("server at process %d is ready to accept another connection.\n",
           getpid());
    caddrlen = sizeof(struct sockaddr_in);
  }

  return ret;
}

static void cleanup() {
  if (sfd >= 0)
    close(sfd);
  if (cfd >= 0)
    close(cfd);
  printf("server at process %d cleaned up and exiting ...\n", getpid());
}

static void docleanup(int signum) {
  if (SIGINT == signum)
    printf("User pressed CTRL-C\n");
  exit(signum);
}

static void print_net_msg(char *msgprefix, struct sockaddr_in *addr) {
  char str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(addr->sin_addr), str, INET_ADDRSTRLEN);
  printf("%s %s:%d\n", msgprefix, str, ntohs(addr->sin_port));
}
