#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include <iostream>

class Complex {
 private:
  int x_;
  int y_;
  // declared as a friend to have access to private fields
  friend std::ostream& operator<<(std::ostream&, const Complex&);

 public:
  Complex(int x, int y) : x_(x), y_(y){};
};

// this line is optional
// std::ostream& operator<<(std::ostream&, const Complex&);

template <>
struct fmt::formatter<Complex> : ostream_formatter {};
template <>
struct fmt::formatter<Complex*> : ostream_formatter {};
