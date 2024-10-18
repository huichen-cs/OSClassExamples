#include "vector.h"
#include <iostream>
#include <unistd.h>

using namespace cisc3320;
using namespace std;

int main() {
  RandomVector rv1(3);
  RandomVector rv2(3);

  double p = rv1.dotProduct(rv2);

  cout << "rv1=" << rv1 << endl;
  cout << "rv2=" << rv2 << endl;
  cout << "DotProduct(rv1,rv2)=" << p << endl;

  sleep(3600);
  return 0;
}
