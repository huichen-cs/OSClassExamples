#include <stdio.h>
#include <unistd.h>
#include <threadpool.h>

void* print_message(void *args) {
    for (int i=0; i<100; i++) {
        long i = (long)args;
        printf("Hello from thread %ld\n", i);
        usleep(50000);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    // printf("1.-------------------\n");
    thread_pool_t *tp = thread_pool_create(4, 256);
    // printf("2.-------------------\n");

    for (int i=0; i<100; i++) {
        thread_pool_add_task(tp, &print_message, (void *)((long)i));
    }

    thread_pool_wait(tp);

    // printf("3.-------------------\n");

    thread_pool_destroy(tp);
    // printf("4.-------------------\n");

    return 0;
}