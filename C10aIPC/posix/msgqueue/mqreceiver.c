#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#include "protocol.h"

int main(int argc, char* argv[]) {
    mqd_t mqd;
    struct mq_attr attr;
    char buffer[MAX_MSG_SIZE];

    attr.mq_flags = 0;              /* Flags (ignored for mq_open()) */
    attr.mq_maxmsg = 10;            /* Max. # of messages on queue */
    attr.mq_msgsize = MAX_MSG_SIZE; /* Max. message size (bytes) */
    attr.mq_curmsgs = 0;            /* # of messages currently in queue
                                       (ignored for mq_open()) */

    mqd = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0644, &attr);
    if (-1 == mqd) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ssize_t nbread;
        nbread = mq_receive(mqd, buffer, MAX_MSG_SIZE, NULL);
        if (-1 == nbread) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        printf("Received: %.*s\n", (int)nbread, buffer);

        if (memcmp(buffer, MSG_LOOP_EXIT, strlen(MSG_LOOP_EXIT)) == 0) {
            printf("Since the writer said Goodbye, exit ...\n");
            break;
        }
    }

    if (-1 == mq_close(mqd)) {
        perror("mq_close");
        exit(EXIT_FAILURE);
           
    }

    if (-1 == mq_unlink(MQ_NAME)) {
        perror("mq_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
