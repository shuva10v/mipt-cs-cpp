#include "complex.h"

std::ostream &operator<<(std::ostream &s, const Complex &c) {
  return s << "Complex number x=" << c.x_ << ", y=" << c.y_;
}