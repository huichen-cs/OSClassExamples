#include "vector.h"
#include <iostream>
#include <unistd.h>

int main() {
  osclasses::RandomVector rv1(3);
  osclasses::RandomVector rv2(3);

  double p = rv1.dotProduct(rv2);

  std::cout << "rv1=" << rv1 << std::endl;
  std::cout << "rv2=" << rv2 << std::endl;
  std::cout << "DotProduct(rv1,rv2)=" << p << std::endl;

  sleep(3600);
  return 0;
}
