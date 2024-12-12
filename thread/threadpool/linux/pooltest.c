#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <threadpool.h>
#include <unistd.h>

void *print_message(void *args) {
  for (int i = 0; i < 100; i++) {
    int32_t i = (intptr_t)args;
    printf("Hello from thread %" PRId32 "\n", i);
    usleep(50000);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  // printf("1.-------------------\n");
  thread_pool_t *tp = thread_pool_create(4, 256);
  // printf("2.-------------------\n");

  for (int i = 0; i < 100; i++) {
    thread_pool_add_task(tp, &print_message, (void *)((intptr_t)i));
  }

  thread_pool_wait(tp);

  // printf("3.-------------------\n");

  thread_pool_destroy(tp);
  // printf("4.-------------------\n");

  return 0;
}
