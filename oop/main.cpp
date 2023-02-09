#include <iostream>

#include "bank.h"

int main() {
  std::cout << "Hello world" << std::endl;
  // Account* prohibited = new Account(100, "RUR", "vasya");
  Account* acc1 = Bank::createPremium("vasya");
  Account* acc2 = Bank::create("masha");

  //   std::cout << acc1->getName() << std::endl;

  // Account copy = *acc1;
  // std::cout << &copy << " " << acc1 << "\n";
  // copy.print();
  acc1->print();
  acc2->print();
  acc1->take(50, "RUB");
  acc1->print();
  acc1->take(60, "RUB");
  acc1->print();

  delete acc1;
  delete acc2;
  // acc1->amount_ -= 50;
  // acc2->amount_ += 50;
  // acc1.print();
}