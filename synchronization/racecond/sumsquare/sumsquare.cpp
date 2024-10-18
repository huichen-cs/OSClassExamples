#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

static int sum = 0;

static void square(int n) { sum += n * n; }

int main(int argc, char *argv[]) {
  std::thread *workers;
  int nworkers = 10;

  if (argc >= 2) {
    nworkers = std::stoi(argv[1]);
  }

  workers = (std::thread *)malloc(sizeof(std::thread) * nworkers);
  if (workers == NULL) {
    std::cerr << "Memory allocation failed\n" << std::endl;
    return EXIT_FAILURE;
  }

  /* Compute
   * 1*1 + 2*2 + 3*3 + ... + (nworkers+1)*(nworkers+1)
   * The expect result is
   *      385 if nworkers is 10,
   *     2870 if nworkers is 20
   */
  for (int i = 0; i < nworkers; i++) {
    workers[i] = std::thread(&square, i + 1);
  }

  for (int i = 0; i < nworkers; i++) {
    workers[i].join();
  }

  std::cout << "sum = " << sum << std::endl;
  return 0;
}
