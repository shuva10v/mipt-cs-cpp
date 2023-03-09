#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <thread>

class User {
 private:
  int i_;

 public:
  User(int i) : i_(i){};
  ~User() { std::cout << "Called destructor for #" << i_ << "\n"; };
  int get() { return i_; };
  void print() const { std::cout << "User #" << i_ << "\n"; };
};
void sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(1000)); }

User* create(int num) { return new User(num); }

class MaxUserHolder {
 private:
  User* max_ = nullptr;

 public:
  void print() const {
    std::cout << "Best user #" << (max_ != nullptr ? max_->get() : -1) << "\n";
  };
  void update(User* user) {
    if (max_ == nullptr || (user != nullptr && max_->get() < user->get())) {
      max_ = user;
    }
  }
};

void object_on_stack() {
  User u1 = User(12);
  User u2(13);
  auto u3 = User(14);
}

void object_on_heap() {
  User* u1 = new User(12);
  auto u2 = new User(12);
  delete u1;
  delete u2;
}

void ownership_problem() {
  MaxUserHolder holder;
  srand(time(NULL));
  for (int i = 0; i < 200; i++) {
    auto u1 = create(rand());
    u1->print();
    holder.update(u1);
    // delete u1;
  }
  holder.print();
}

class RandomLetters {
 private:
  char* arr_;
  int len_;

 public:
  RandomLetters(const RandomLetters& other) {
    std::cout << "Calling copy ctor for " << other.arr_ << "\n";
    len_ = other.len_;
    arr_ = new char[len_];
    std::copy(other.arr_, other.arr_ + len_, arr_);
  };

  RandomLetters(int num) : len_(num) {
    srand(time(NULL));
    arr_ = new char[num];
    for (int i = 0; i < num - 1; ++i) {
      arr_[i] = 97 + rand() % 25;
    }
    arr_[num - 1] = 0;
    std::cout << "Called ctor for " << arr_ << "(" << (void*)arr_ << ")\n";
  };

  ~RandomLetters() {
    std::cout << "Calling destructor for " << arr_ << "(" << (void*)arr_ << ")"
              << " \n";
    delete[] arr_;
  };

  RandomLetters& operator=(const RandomLetters& other) {
    std::cout << "Copy assignment operator for " << arr_ << "\n";
    if (this != &other) {
      RandomLetters tmp(other);
      std::swap(arr_, tmp.arr_);
      std::swap(len_, tmp.len_);
    }
    return *this;
  };

  const char* get() { return arr_; };
};

void destructor() {
  auto r1 = RandomLetters(10);
  auto r2 = RandomLetters(20);
  std::cout << "r1: " << r1.get() << ", r2: " << r2.get() << "\n";
}

void destructor2() {
  auto r1 = RandomLetters(10);
  auto r2 = RandomLetters(20);
  r2 = r1;
  std::cout << "r1: " << r1.get() << ", r2: " << r2.get() << "\n";
}

class MaxUserHolderV2 {
 private:
  std::shared_ptr<User> max_;

 public:
  void print() const {
    std::cout << "Best user #" << (max_ ? max_->get() : -1) << "\n";
  };
  void update(std::shared_ptr<User> user) {
    if (!max_ || (user && max_->get() < user->get())) {
      max_ = user;
    }
  }
};

void ownership_problem2() {
  MaxUserHolderV2 holder;
  srand(time(NULL));
  for (int i = 0; i < 5; i++) {
    auto u1 = std::make_shared<User>(rand());
    u1->print();
    holder.update(u1);
    // delete u1;
  }
  holder.print();
}

std::shared_ptr<User> create_ptr(int arg) {
  return std::shared_ptr<User>(new User(arg));
}

void smart_ptrs1() {
  std::shared_ptr<User> u1 = create_ptr(10);
  std::shared_ptr<User> u2 = u1;
  std::cout << "Owners: " << u1.use_count() << "\n";
  u1->print();
  u2->print();
}

void smart_ptrs2() {
  std::unique_ptr<User> u1 = std::make_unique<User>(12);
  // doesn't work: std::unique_ptr<User> u2 = u1;
  u1->print();
}

int main() { smart_ptrs2(); }
