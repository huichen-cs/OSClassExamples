#include <unistd.h>
#include <iostream>
#include "vector.h"

using namespace cisc3320;
using namespace std;

int main() {
	RandomVector rv1(5);
	RandomVector rv2(5);

	double p = rv1.dotProduct(rv2);
	
	cout << "rv1=" << rv1 << endl;
	cout << "rv2=" << rv2 << endl;
	cout << "DotProduct(rv1,rv2)=" << p << endl;

	sleep (360);
	return 0;
}
