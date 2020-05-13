#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxiters = 20;
static void computeOnBuf(int size, int *buf);

int main(int argc, char *argv[]) {
    int hugepagesize;
    int numhugepages;
    size_t size;    
    int *buf = NULL;
    clock_t t0, t1;

    if (argc < 3) {    
        fprintf(stderr, "\tUsage: %s hugepage_size_in_KB num_of_hugepages\n", 
                argv[0]);
        exit(EXIT_FAILURE);
    }


    sscanf(argv[1], "%d", &hugepagesize);
    sscanf(argv[2], "%d", &numhugepages);

    printf("\tHugepage size:    %d KB\n", hugepagesize);
    printf("\tNum of Hugepages: %d pages\n", numhugepages);

    size = hugepagesize*numhugepages*1024;
    buf = (int*)malloc(size);
    if (buf == NULL) {
        fprintf(stderr, "\tFailed to allocate %d bytes to the buf array.", 
                size);
        exit (EXIT_FAILURE);
    }
    printf("\tAllocated %d bytes to the buf array\n", size);
    

    printf("\tDoing computation using the buf array\n");
    t0 = clock();
    computeOnBuf(size/sizeof(int), buf);
    t1 = clock();
    printf("\tThe computation consumed about %.2f seconds\n", 
           (double)(t1 - t0)/(double)CLOCKS_PER_SEC);

    if (buf != NULL) free(buf);
    return 0;
}

static void computeOnBuf(int size, int *buf) {
    for (int j=0; j<maxiters; j++) {
      /*
        for (int i=0; i<size; i++) {
            int idx;
            if (i % 2 == 0) idx = i;
            else idx = size - i;
            buf[idx] = i + 1;
        }

        for (int i=0; i<size; i+=1024) {
            buf[i] = buf[i]*buf[i];
        }

        for (int i=0; i<size; i++) {
            buf[i] = size - 1;
        }
        */
        
        for (int i=0; i<size; i++) {
            buf[random() % size] = buf[random() % size ]*buf[random() % size];
        }
    }
}
