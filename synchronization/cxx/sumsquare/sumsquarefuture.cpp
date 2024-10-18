#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <vector>

static int square(int n) { return n * n; }

int main(int argc, char *argv[]) {
  int nworkers = 10;

  if (argc >= 2) {
    nworkers = std::stoi(argv[1]);
  }

  /* Compute
   * 1*1 + 2*2 + 3*3 + ... + (nworkers+1)*(nworkers+1)
   * The expect result is
   *      385 if nworkers is 10,
   *     2870 if nworkers is 20
   */
  int sum = 0;
  for (int i = 0; i < nworkers; i++) {
    std::future<int> s = std::async(&square, i + 1);
    sum += s.get();
  }

  std::cout << "sum = " << sum << std::endl;
  return 0;
}
