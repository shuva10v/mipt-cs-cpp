#include <iostream>
#include <memory>

class Chessman {
 public:
  virtual void move(int i, int j) = 0;
};

class OrdinaryChessman : public Chessman {
 private:
  int i_, j_;

 public:
  OrdinaryChessman() : i_(0), j_(0){};
  void move(int i, int j) override {
    i_ = i;
    j_ = j;
  };
};

class LoggingDecorator : public Chessman {
 private:
  std::shared_ptr<Chessman> src_;

 public:
  LoggingDecorator(std::shared_ptr<Chessman> src) : src_(src){};
  void move(int i, int j) override {
    std::cout << "Moving to " << i << " " << j << "\n";
    src_->move(i, j);
  }
};

class CountingDecorator : public Chessman {
 private:
  std::shared_ptr<Chessman> src_;
  int movesCount_ = 0;

 public:
  CountingDecorator(std::shared_ptr<Chessman> src) : src_(src){};
  void move(int i, int j) override {
    movesCount_++;
    src_->move(i, j);
  }

  int moves() { return movesCount_; };
};

int main() {
  std::cout << "Running decorator example\n";
  auto chessman = std::shared_ptr<Chessman>(new OrdinaryChessman());
  chessman->move(4, 5);
  chessman = std::shared_ptr<Chessman>(new LoggingDecorator(chessman));
  chessman->move(3, 4);
  std::shared_ptr<CountingDecorator> finalChessman =
      std::shared_ptr<CountingDecorator>(new CountingDecorator(chessman));

  finalChessman->move(1, 2);
  finalChessman->move(2, 3);
  std::cout << "Total moves: " << finalChessman->moves() << "\n";

  return 0;
}