#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void print_net_msg(char *msgprefix, struct sockaddr_in *addr);
static void cleanup();
static void docleanup(int signum);
static void *clientwrapper(void *arg);
static int handleclient(int cfd);

static const char *SERVER_ADDR = "0.0.0.0";
static const int   SERVER_PORT =     61234;
static const int   BACKLOG     =         5;

static int sfd = -1, cfd = -1;
static pthread_attr_t tattr;

int main(int argc, char *argv[]) {
    pthread_t tid;
    int ret = EXIT_SUCCESS;
    socklen_t caddrlen;
    struct sockaddr_in saddr, caddr;
    struct sigaction sigact;

    printf("server starts running at process %d ...\n", getpid());

    atexit(cleanup);
    sigact.sa_handler = docleanup;
    sigaction(SIGINT, &sigact, NULL);

    if (0 != pthread_attr_init(&tattr)) {
        fprintf(stderr, "pthread_attr_init error\n");
        exit(EXIT_FAILURE);
    }

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
    printf("server at process %d is ready to accept connection.\n", 
            getpid());

    caddrlen = sizeof(struct sockaddr_in);
    while ((cfd = accept(sfd, (struct sockaddr *)&caddr, &caddrlen)) >= 0) {
        if (-1 == cfd) {
            perror("accept");
            ret = EXIT_FAILURE;
            break;
        }
        print_net_msg("server accepted connection from", &caddr);

        if (0 != pthread_create(&tid, &tattr, clientwrapper, &cfd)) {
            fprintf(stderr, "pthread_create failed\n");
            ret = EXIT_FAILURE;
            break;
        }
        printf("server created thread %lu to handle the incoming client\n", 
                tid);
        printf("server at process %d is ready to accept another connection.\n",
                getpid());
        caddrlen = sizeof(struct sockaddr_in);
    }

    return ret;
}

static void *clientwrapper(void *arg) {
    int cfd = *((int *)arg);
    handleclient(cfd);
    pthread_exit(NULL);
}

static int handleclient(int cfd) {
    pid_t pid = getpid();
    int bytesreceived;
    char buf[128];

    printf("thread %lu @ process %d is handling client\n", pthread_self(), pid);
    while(1) {
        bytesreceived = recv(cfd, buf, sizeof(buf)-1, 0);
        if (-1 == bytesreceived) {
            perror("recv");
            return EXIT_FAILURE;
        }
        buf[bytesreceived] = '\0';
        printf("received from client at thread %lu @ process %d: %s\n", 
                pthread_self(), getpid(), buf);
        if (-1 == send(cfd, buf, bytesreceived, MSG_NOSIGNAL)) {
            perror("send");
            return EXIT_FAILURE;
        } 
        printf("echoed back to client at thread %lu @ process %d: %s\n", 
                pthread_self(), getpid(), buf);
        if (strncasecmp(buf, "Bye!", 4) == 0) {
            break;
        }
    }
    printf("client said 'Bye!', and thread %lu @ process %d exiting ...\n", 
            pthread_self(), getpid());
    return EXIT_SUCCESS;
}

static void cleanup() {
    if (sfd >=0) close(sfd);
    if (cfd >=0) close(cfd);
    pthread_attr_destroy(&tattr);
    printf("server at process %d cleaned up and exiting ...\n", getpid());
}

static void docleanup(int signum) {
    if (SIGINT == signum) printf("User pressed CTRL-C\n");
    exit(signum);
}

static void print_net_msg(char *msgprefix, struct sockaddr_in *addr) {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr->sin_addr), str, INET_ADDRSTRLEN);
    printf("%s %s:%d\n", msgprefix, str, ntohs(addr->sin_port));
}
