#include <iostream>

class Duration {
 private:
  int minutes_;
  int seconds_;

 public:
  Duration(int min, int sec) : minutes_(min), seconds_(sec){};
  void print() {
    std::cout << minutes_ << " m, " << seconds_ << " s"
              << "\n";
  };

  // member functions
  explicit operator bool() { return minutes_ + seconds_ > 0; };

  explicit operator int() { return minutes_ * 60 + seconds_; };

  Duration& operator++() {
    seconds_++;
    if (seconds_ >= 60) minutes_ += 1;
    return *this;
  }

  Duration operator+(const Duration& rhs) {
    int m = minutes_ + rhs.minutes_;
    int s = seconds_ + rhs.seconds_;
    return Duration(m + s / 60, s % 60);
  };

  // alternative: declare as friend non-member function
  // friend Duration operator+(const Duration& lhs, const Duration& rhs) {
  //   int m = lhs.minutes_ + rhs.minutes_;
  //   int s = lhs.seconds_ + rhs.seconds_;
  //   return Duration(m + s / 60, s % 60);
  // };

  // the same, but the right hand side is int
  friend Duration operator+(const Duration& lhs, int seconds) {
    int m = lhs.minutes_;
    int s = lhs.seconds_ + seconds;
    return Duration(m + s / 60, s % 60);
  };

  friend Duration operator+(int seconds, const Duration& lhs) {
    int m = lhs.minutes_;
    int s = lhs.seconds_ + seconds;
    return Duration(m + s / 60, s % 60);
  };
};

int main() {
  Duration d1 = Duration(1, 10);
  Duration d2 = Duration(3, 55);
  ++d1;
  d1.print();
  d2.print();

  Duration sum = d1 + d2;
  sum.print();
  (sum + 60).print();
  (60 + sum).print();

  if (d1) {
    std::cout << "Non zero\n";
  }

  // or static_cast<int>(d1)
  std::cout << (int)(d1) << "\n";
}