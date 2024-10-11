#define _GNU_SOURCE /* See feature_test_macros(7) */
#include "tasks.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

extern int *numbers;
extern int num_numbers;

void *find_min(void *param) {
  if (numbers == NULL) {
    fprintf(stderr, "Array numbers not initialized\n");
    exit(EXIT_FAILURE);
  }

  int min = numbers[0];
  for (int i = 1; i < num_numbers; i++) {
    if (numbers[i] < min) {
      min = numbers[i];
    }
  }

  printf("In thread %d, got min = %d\n", syscall(SYS_gettid), min);

  *(double *)param = min;
}

void *find_max(void *param) {
  if (numbers == NULL) {
    fprintf(stderr, "Array numbers not initialized\n");
    exit(EXIT_FAILURE);
  }

  int max = numbers[0];
  for (int i = 1; i < num_numbers; i++) {
    if (numbers[i] > max) {
      max = numbers[i];
    }
  }

  printf("In thread %d, got max = %d\n", syscall(SYS_gettid), max);

  *(double *)param = max;
}

void *compute_sum(void *param) {
  if (numbers == NULL) {
    fprintf(stderr, "Array numbers not initialized\n");
    exit(EXIT_FAILURE);
  }

  double sum = 0.;
  for (int i = 0; i < num_numbers; i++) {
    sum += (double)numbers[i];
  }

  printf("In thread %d, got sum = %f\n", syscall(SYS_gettid), sum);

  *(double *)param = sum;
}

void *compute_average(void *param) {
  if (numbers == NULL) {
    fprintf(stderr, "Array numbers not initialized\n");
    exit(EXIT_FAILURE);
  }

  double average = 0.;
  for (int i = 0; i < num_numbers; i++) {
    average = (double)numbers[i] / (double)(i + 1) +
              (double)i / (double)(i + 1) * average;
  }

  printf("In thread %d, got average = %f\n", syscall(SYS_gettid), average);

  *(double *)param = average;
}
