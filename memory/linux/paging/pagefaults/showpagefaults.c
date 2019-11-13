/**
 * Using a few tools to get a little more insights into memory 
 * usage of a program, e.g.,
 *  ps -o size,rss YOUR_PID
 *  pmap -d YOUR_PID
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_page_fault_stat(int pid);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s number_of_pages\n", argv[0]);
        return 0;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    int pagesize = getpagesize(), pid = getpid();

    char *p;
    
    p = malloc(pagesize * n);
    
    printf("doing the loop ...\n");
    
    for (int i=0; i<pagesize * n; i++) {
        p[i] = i % 256; 
        if (i % pagesize == 0) {
            printf("Page#: %d\n", i/pagesize);
        }
    }

    printf("completed the loop ...\n");
    free(p);
    print_page_fault_stat(pid);
    printf("page size = %d bytes pid = %d\n", pagesize, pid); 

    sleep(60);
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

