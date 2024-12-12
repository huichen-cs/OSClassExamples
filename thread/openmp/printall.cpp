#include <iostream>

int main(int argc, char *argv[]) {
  int numbers[10];
  for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
    numbers[i] = i;
  }

#pragma omp parallel for
  for (int i = 0; i < sizeof(numbers) / sizeof(int); i++) {
    printf("%d\n", numbers[i]);
  }

  return 0;
}
