#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>

static void cleanup();
static void docleanup();

static const char *SERVER_ADDR = "127.0.0.1";
static const int   SERVER_PORT =       61234;

static int cfd = -1;

int main(int argc, char *argv[]) {
    struct sockaddr_in saddr;
    char buf[128];
    int bufsize = 128,
        bytesread;
    struct sigaction sigact;

    printf("client starts running ...\n");

    atexit(cleanup);
    sigact.sa_handler = docleanup;
    sigaction(SIGINT, &sigact, NULL);

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == cfd) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(SERVER_PORT);
    if (0 == inet_pton(AF_INET, SERVER_ADDR, &saddr.sin_addr)) {
        fprintf(stderr, "cannot convert %s to IP address\n", SERVER_ADDR);
        exit(EXIT_FAILURE);
    }
    if (-1 == connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr))) {
       perror("connect"); 
       exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter message: ");

        if (NULL == fgets(buf, bufsize-1, stdin)) {
            fprintf(stderr, "failed to read stdin\n"); 
            exit(EXIT_FAILURE);
        }
        buf[strcspn(buf, "\r\n")] = '\0';
        printf("user entered: %s\n", buf);

        if (-1 == send(cfd, buf, bufsize-1, MSG_NOSIGNAL)) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("client sent: %s\n", buf);

        bytesread = recv(cfd, buf, bufsize, 0);
        if (-1 == bytesread) {
            perror("recv");
            exit(EXIT_FAILURE);
        } 
        buf[bytesread] = '\0';
        printf("client received: %s\n", buf);
        if (strncasecmp(buf, "Bye!", 4) == 0) {
            printf("server echoed 'Bye!', and exiting ...\n");
            break;
        }
    }

    return 0;
}

static void cleanup() {
    if (cfd >= 0) close(cfd);
    printf("client cleaned up and exiting ...\n");
}

static void docleanup(int signum) {
    if (SIGINT == signum) printf("User pressed CTRL-C\n");
    exit(signum);
} 
