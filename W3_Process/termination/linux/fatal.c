#include <stdio.h>

int main() {
    int *ptr = 0;

    printf("attempt to assign 12345 to *ptr=%p\n", ptr); 
    *ptr = 12345;

    return 0;
}
