#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "part_sum.h"
#include "util.h"

extern int *numbers;       /* this data is shared by the threads      */
extern int *indices;       /* this data is also shared by the threads */
extern int64_t *part_sums; /* this data is also shared by the threads */

/* The thread will execute in this function */
void *part_sum_runner(void *param) {
  int worker_idx = *((int *)param);

  int64_t sum = 0;

  int begin = indices[worker_idx * 2];
  int end = indices[worker_idx * 2 + 1];

  /*
  printf("In thread with worker_idx=%d size=%d begin=%d end=%d\n",
    worker_idx, end-begin+1, begin, end);
  print_array("part_numbers", end-begin+1, numbers+begin);
  */

  for (int i = begin; i <= end; i++) {
    sum += numbers[i];
  }

  part_sums[worker_idx] = sum;

  printf("worker (worker_idx=%d) exited\n", worker_idx);
  pthread_exit(0);
}
