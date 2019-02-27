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
    char *messages[] = {
        "Hello, Reciever!",
        "Hello again, do you hear me, Receiver!",
        "No reply, so rude!",
        "Goodbye!"
    };


    attr.mq_flags = 0;              /* Flags (ignored for mq_open()) */
    attr.mq_maxmsg = 10;            /* Max. # of messages on queue */
    attr.mq_msgsize = MAX_MSG_SIZE; /* Max. message size (bytes) */
    attr.mq_curmsgs = 0;            /* # of messages currently in queue
                                       (ignored for mq_open()) */

    mqd = mq_open(MQ_NAME, O_RDONLY | O_CREAT, 0644, &attr);
    if (-1 == mqd) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<sizeof(messages)/sizeof(char *); i++) {
        ssize_t nbread;
        nbread = mq_send(mqd, messages[i], strlen(messages[i])+1, 0); 
        if (-1 == nbread) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
    }

    if (-1 == mq_close(mqd)) {
        perror("mq_close");
        exit(EXIT_FAILURE);
           
    }

    return 0;
}
