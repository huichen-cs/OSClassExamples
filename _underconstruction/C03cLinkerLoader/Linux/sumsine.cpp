#include <cmath>

#include "sumsine.h"

double sumsine() {
    double sum = 0.;
    for (int a=0; a<=180; a++) {
        double angle = a / 3.1415926; 
        sum += sin(angle);
    }
    return sum;
}
