#include <iostream>

#include <cstring>  /* to use strerror: see "man 3 strerror"    */
#include <cstdlib>  /* to use exit: see "man 3 exit"            */

#include <sys/types.h>  /* to use open: see "man 2 open"        */
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> /* to use close: see "man 2 close"          
                     * to use read:  see "man 2 read "          
                     * to use write: see "man 2 write"          */


static void usage(char* app);
static void exit_if_failed(char *pathname, int fd);
static void exit_if_failed(char *srcpathname, char *dstpathname, int status);
static int copyfile(int srcfd, int destfd);

static const int BUFFER_SIZE = 1024 * 1024;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        usage(argv[0]);
        return 0;
    }

    int srcfd = open(argv[1], O_RDONLY);
    exit_if_failed(argv[1], srcfd);

    int dstfd = open(argv[2], O_WRONLY|O_CREAT|O_EXCL);
    exit_if_failed(argv[2], dstfd);

    int status = copyfile(srcfd, dstfd);
    exit_if_failed(argv[1], argv[2], status);

    close(srcfd);
    close(dstfd);

    std::cout << "copyed " << argv[1] << " to " << argv[2] << std::endl;

    return EXIT_SUCCESS;
}

static void usage(char* app) {
    std::cout << "Usage: " << app << " src_file dest_file" << std::endl;
}

static void exit_if_failed(char *pathname, int fd) {
    if (fd == -1) {
        std::cerr 
            << "When " << pathname 
            << " being opened error occured with error no: " 
            << errno << " and error message: "
            << strerror(errno) 
            << std::endl;
        exit(EXIT_FAILURE);
    }
}

static void exit_if_failed(char *srcpathname, char *dstpathname, int status) {
    if (status == -1) {
        std::cerr 
            << "When " << srcpathname << " was being copied to " << dstpathname 
            << " error occured with error no: " 
            << errno << " and error message: "
            << strerror(errno) 
            << std::endl;
        exit(EXIT_FAILURE);
    }
}

static int copyfile(int srcfd, int dstfd) {
    char buffer[BUFFER_SIZE];
    int bytesread, byteswritten;

    while ((bytesread = read(srcfd, buffer, BUFFER_SIZE)) > 0) {
        byteswritten = write(dstfd, buffer, bytesread);
        if (byteswritten == -1) return -1;
    }

    if (bytesread == -1) return -1;
    return 0;
}
