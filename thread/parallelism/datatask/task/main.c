#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tasks.h"
#include "util.h"

int *numbers;                   /* this data is shared by the threads      */
int num_numbers;

static int *mk_random_numbers(int n);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s number_of_random_integers\n", argv[0]);
    return 0;
  }

  num_numbers = atoi(argv[1]);

  numbers = mk_random_numbers(num_numbers);
  print_array("numbers", num_numbers, numbers);
    

  pthread_t *tids;  /* the thread identifier */
  pthread_attr_t *attrs; /* set of thread attributes */

  /* create the threads and distribute work among the threads  */
  void *(*worker[])(void *) = { 
        find_min, find_max, compute_sum, compute_average };
  int num_threads = sizeof(worker)/sizeof(void *);
  printf("number of threads = %d\n", num_threads);
  tids = (pthread_t *)malloc(sizeof(pthread_t)*num_threads);
  attrs = (pthread_attr_t *)malloc(sizeof(pthread_attr_t)*num_threads);
  double *results = malloc(sizeof(double)*num_threads);

  for (int i=0; i<num_threads; i++) {
     /* set the default attributes of the thread */
     pthread_attr_init(attrs+i);
     tids[i] = i;

     pthread_create(tids+i, attrs+i, worker[i], results+i);

     printf("worker %d created.\n", i);
  }

  for (int i=0; i<num_threads; i++) {
     /* wait for the thread to exit */
     pthread_join(tids[i],NULL);
  }

  for (int i=0; i<num_threads; i++) {
    printf("results[%d] = %f\n", i, results[i]);
  }

  free(numbers);
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

