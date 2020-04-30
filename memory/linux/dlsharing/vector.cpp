#include <stdexcept>
#include <cstdlib>
#include "vector.h"

using namespace cisc3320;

double Vector::dotProduct(Vector v) const {
	if (size != v.size) {
		throw std::runtime_error("Vector sizes do not gree.");
	}

	double sum = 0.0;

	for (int i=0; i<size; i++) {
		sum += value[i] * v.value[i];
	}	
	return sum;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << "{size=" << v.size << "," << "values=[";
	for (int i=0; i<v.size; i++) {
		os << v.value[i];
		if (i < v.size-1) os << ",";
	}
	os << "]}";
	return os;
}

RandomVector::RandomVector(const int size) {
	this->size = size;
	value = new double[size];
	for (int i=0; i<size; i++) {
		value[i] = (double)random()/((double)(RAND_MAX)+1.);
	}
}

RandomVector::~RandomVector() {
	delete[] value;
}
