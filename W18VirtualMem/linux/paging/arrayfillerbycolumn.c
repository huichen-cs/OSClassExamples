/**
 * Using a few tools to get a little more insights into memory 
 * usage of a program, e.g.,
 *  ps -o size,rss YOUR_PID
 *  pmap -d YOUR_PID
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/user.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

void print_page_fault_stat(int pid);
static int  a[1024][1024];

int main(int argc, char *argv[]) {
    int nrows = PAGE_SIZE/sizeof(int), 
        ncols = PAGE_SIZE/sizeof(int);
    struct rlimit rlim;

    printf("nrows = %d ncols = %d\n", nrows, ncols);

    rlim.rlim_cur = PAGE_SIZE*1;
    rlim.rlim_max = PAGE_SIZE*1;
    if (-1 == setrlimit(RLIMIT_DATA, &rlim)) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    for(int j=0; j<ncols; j++) {
        for(int i=0; i<nrows; i++) {
            a[i][j] = 0;
        }
    }

    print_page_fault_stat(getpid());

    return 0;
}

void print_page_fault_stat(int pid) {
    char buf[1024];
    snprintf(buf, sizeof(buf), "/proc/%d/stat", pid);

    FILE *fd = fopen(buf, "rt");
    if (NULL == fd) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    if (NULL == fgets(buf, sizeof(buf), fd)) {
        fprintf(stderr, "failed to read process stat\n");
        exit(EXIT_FAILURE);
    }

    int fields = 0, i=0;
    const int PAGE_FAULT_POS = 9;
    while (buf[i] != '\0' && i < sizeof(buf)) {
        if (buf[i] == ' ') fields ++;
        i ++;
        if (fields >= PAGE_FAULT_POS) break;
    }

    int minflt, cminflt, majflt, cmajflt;
    if (fields == PAGE_FAULT_POS) {
        sscanf(buf+i, "%d %d %d %d", &minflt, &cminflt, &majflt, &cmajflt);
        printf("minor faults              = %d\n"
               "minor faults (with child) = %d\n"
               "major                     = %d\n"
               "major faults (with child) = %d\n", 
               minflt, cminflt, majflt, cmajflt);
    }

    fclose(fd);
}

