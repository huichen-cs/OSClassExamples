#include <iostream>
using namespace std;

// static int* mk_rand_nums(int n);
static int *mk_nums(int n);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: sumall <number of integers>" << endl;
    return 0;
  }

  int n;
  sscanf(argv[1], "%d\n", &n);

  // int* numbers = mk_rand_nums(n);
  int *numbers = mk_nums(n);
  long long sum = 0l;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++) {
    sum += numbers[i];
  }
  cout << "The sum is " << sum << endl;

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
