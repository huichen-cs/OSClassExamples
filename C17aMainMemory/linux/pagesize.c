#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int pagesize = getpagesize();
    printf("Page size = %d bytes\n", pagesize);
    return 0;
}
