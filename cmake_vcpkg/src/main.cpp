#include <spdlog/spdlog.h>

#include <iostream>

#include "complex.h"

int main(int, char**) {
  // std::cout << "Hello, world!\n";
  spdlog::info("Say hello to spdlog!");

  // using placeholders
  int value = 100;
  spdlog::warn("Value is {}", value);

  // working with floating points
  spdlog::info("Support for floats {:.2f}, {:.1f}", 1.23456, 100210201.2323232);

  // declaring custom formatter to your own classes
  Complex c1 = Complex(10, 20);
  spdlog::info("Complex c1: {}", c1);

  // the same with pointers
  Complex* c2 = new Complex(10, 20);
  spdlog::info("Complex c1: {}, raw pointer: {}", *c2, fmt::ptr(c2));
  delete c2;
}
