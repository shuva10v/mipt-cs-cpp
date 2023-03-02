#include <iostream>

int max_v1(int left, int right) {
  if (left < right) {
    return right;
  } else {
    return left;
  }
};

double max_v1(double left, double right) {
  if (left < right) {
    return right;
  } else {
    return left;
  }
};

std::string max_v1(std::string left, std::string right) {
  if (left < right) {
    return right;
  } else {
    return left;
  }
};

template <typename T>
T max_v2(T left, T right) {
  if (left < right) {
    return right;
  } else {
    return left;
  }
};

class ReminderContainer {
 private:
  int i_;

 public:
  ReminderContainer(int i) : i_(i){};
  int get() { return i_; };
};

template <>
ReminderContainer max_v2(ReminderContainer left, ReminderContainer right) {
  if (left.get() % 10 < right.get() % 10) {
    return right;
  } else {
    return left;
  }
};

int main() {
  std::cout << max_v1(100, 200) << "\n";
  std::cout << max_v1(40.1, 10.2) << "\n";
  std::cout << max_v1("left", "right") << "\n";
  //
  std::cout << "Template version\n";

  std::cout << max_v2<int>(100, 200) << "\n";
  std::cout << max_v2<double>(40.1, 10.2) << "\n";
  std::cout << max_v2<std::string>("left", "right") << "\n";

  //
  std::cout << "Template version with type deduction\n";
  std::cout << max_v2(100, 200) << "\n";
  std::cout << max_v2(40.1, 10.2) << "\n";
  std::cout << max_v2("left", "right") << "\n";

  //
  std::cout << "Template specialization\n";
  std::cout << max_v2(ReminderContainer(11), ReminderContainer(2)).get()
            << "\n";

  return 0;
}