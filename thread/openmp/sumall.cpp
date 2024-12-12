#include <cstdint>
#include <iostream>

// static int* mk_rand_nums(int n);
static int *mk_nums(int n);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: sumall <number of integers>" << std::endl;
    return 0;
  }

  int n;
  sscanf(argv[1], "%d\n", &n);

  // int* numbers = mk_rand_nums(n);
  int *numbers = mk_nums(n);
  int64_t sum = 0l;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++) {
    sum += numbers[i];
  }
  std::cout << "The sum is " << sum << std::endl;

  free(numbers);
  return 0;
}

static int *mk_nums(int n) {
  int *numbers = new int[n];

  for (int i = 0; i < n; i++) {
    numbers[i] = i;
  }

  return numbers;
}

/*
static int* mk_rand_nums(int n) {
    int *numbers = new int[n];

    srand(time(NULL));
    for (int i=0; i<n; i++) {
        numbers[i] = rand() & 0xff;
    }

    return numbers;
}
*/
