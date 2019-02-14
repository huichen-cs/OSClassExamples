/**
 * 1. To compile, run
 *  make
 * 2. Run size as in
 *  size memoryex
 */
#include <stdlib.h>

int x;
int y = 5;


int main(int argc, char *argv[]) {
    int *array;
    int i;
   
    array = (int *)malloc(sizeof(int)*5);

    for (i = 0; i<5; i++) {
        array[i] = i*i;
    }

    free(array);
    return 0;
}

