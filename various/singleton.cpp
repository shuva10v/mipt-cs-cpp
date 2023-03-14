#include <iostream>

class Singleton {
 public:
  static Singleton& getInstance() {
    std::cout << "getInstance called\n";
    static Singleton s;
    return s;
  }
  // disable copy in any form
  Singleton(Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  int param1;
  std::string param2;

 private:
  // only accessible by static getInstance() method
  Singleton() {
    std::cout << "Consutrting singleton\n";
    char* param2_char = std::getenv("PARAM2");
    if (param2_char) {
      param2 = param2_char;
    } else {
      param2 = "";
    }
    char* param1_char = std::getenv("PARAM1");
    if (param1_char != nullptr) {
      param1 = atoi(param1_char);
    } else {
      param1 = 0;
    }
  }
};

int main() {
  std::cout << "Running singleton example\n";
  std::cout << "Singleton address: " << (void*)&(Singleton::getInstance())
            << "\n";
  std::cout << "Singleton address: " << Singleton::getInstance().param1 << "\n";
  std::cout << "Singleton address: " << Singleton::getInstance().param2 << "\n";
  return 0;
}