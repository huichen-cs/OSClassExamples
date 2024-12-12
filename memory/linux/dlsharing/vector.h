#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>

namespace osclasses {
class Vector;
}
std::ostream &operator<<(std::ostream &os, const osclasses::Vector &v);

namespace osclasses {
class Vector {
public:
  double dotProduct(const Vector v) const;
  friend std::ostream & ::operator<<(std::ostream & os, const Vector & v);

protected:
  int size;
  double *value;
};

class RandomVector : public Vector {
public:
  explicit RandomVector(const int size);
  ~RandomVector();
};
}  // namespace osclasses

#endif
