/**
 * use command tty on the command line to query the name of
 * the current terminal
 *
 * e.g., 
 * $ tty
 * /dev/pts/2 
 * where /dev/pts/2 is the name of the current terminal
 *
 * Then you can run this program as in,
 *
 * ./writesth /dev/pts/2 "Hello, World!"
 *
 * which writes the message "Hello, World!" to the terminal.
 *
 * However, if you can also run the program as in,
 *
 * ./writesth hello.txt "Hello, World!"
 *
 * which write the message to the hello.txt file
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>    
#include <string.h>

static void usage(char* appname);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        usage(argv[0]);
        return 0;
    }

    char *dst = argv[1];
    char *msg = argv[2];

    int fd = open(dst, O_WRONLY|O_CREAT);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, msg, strlen(msg));

    close(fd);
    return 0;
}

static void usage(char* appname) {
    printf("Usage: %s destname message\n", appname);
}
