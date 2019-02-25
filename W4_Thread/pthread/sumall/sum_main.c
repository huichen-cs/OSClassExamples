#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "part_sum.h"
#include "util.h"

int *numbers;         /* this data is shared by the threads      */
int *indices;         /* this data is also shared by the threads */
long long *part_sums; /* this data is also shared by the threads */

static int *worker_indices;

static int *mk_random_numbers(int n);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s number_of_threads number_of_random_integers_to_add\n", 
      argv[0]);
    return 0;
  }

  int num_threads = atoi(argv[1]);
  int num_numbers = atoi(argv[2]);
  if (num_numbers < num_threads) {
    printf("Error: for simplicity we don't allow more threads than the number of numbers of add\n");
    exit(EXIT_FAILURE);
  }
  numbers = mk_random_numbers(num_numbers);

  /*
  print_array("numbers", num_numbers, numbers);
  */

  pthread_t *tids;  /* the thread identifier */
  pthread_attr_t *attrs; /* set of thread attributes */


  /* create the threads and distribute work among the threads  */
  part_sums = (long long*)malloc(sizeof(long long)*num_threads); 
  indices = (int *)malloc(sizeof(int)*(num_threads*2));
  worker_indices = (int *)malloc(sizeof(int)*num_threads);
  tids = (pthread_t *)malloc(sizeof(pthread_t)*num_threads);
  attrs = (pthread_attr_t *)malloc(sizeof(pthread_attr_t)*num_threads);

  int part_size = num_numbers / num_threads;
  indices[0] = 0;
  indices[1] = part_size - 1;
  for (int i=1; i<num_threads; i++) {
   indices[i*2] = indices[i*2-1] + 1;
   indices[i*2+1] = indices[i*2] + part_size - 1;
  }
  indices[(num_threads-1)*2+1] = num_numbers-1;
  print_array("indices", num_threads*2, indices);

  for (int i=0; i<num_threads; i++) {
     /* set the default attributes of the thread */
     pthread_attr_init(attrs+i);
     tids[i] = i;
     worker_indices[i] = i;

     pthread_create(tids+i, attrs+i, part_sum_runner, worker_indices+i);

     printf("worker (worker_indices=%d) created.\n", worker_indices[i]);
  }

  for (int i=0; i<num_threads; i++) {
     /* wait for the thread to exit */
     pthread_join(tids[i],NULL);
  }


  long long sum = 0ll;
  for (int i=0; i<num_threads; i++) {
    sum += part_sums[i];
  }
  printf("sum = %lld\n",sum);


  free(numbers);
  free(part_sums);
  free(indices);
  free(worker_indices);
  free(tids);
  free(attrs);
}

static int *mk_random_numbers(int n) {
  int *numbers;	

  numbers = (int*)malloc(sizeof(int)*n);

  srandom(time(NULL));
  for (int i=0; i<n; i++) {
    numbers[i] = random();
  }
 
  return numbers;
}

