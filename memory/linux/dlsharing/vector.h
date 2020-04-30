#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>

namespace cisc3320 { class Vector; }
std::ostream& operator<<(std::ostream& os, const cisc3320::Vector& v);

namespace cisc3320 {
	class Vector {
		public:
			double dotProduct(const Vector v) const;
			friend std::ostream& ::operator<<(std::ostream& os, const Vector& v);
		protected:
			int size;
			double *value;
	};

	class RandomVector:public Vector {
		public:
			RandomVector(const int size);
			~RandomVector();
	};
}

#endif

