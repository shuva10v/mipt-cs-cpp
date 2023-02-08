#include <iostream>
#include "bank.h"

int main() {
    std::cout << "Hello world" << std::endl;
    Account* acc1 = new Account(100, "RUB", "vasya");
    Account* acc2 = new Account(200, "RUB", "masha");
    acc1->print();
    acc2->print();
    // acc1->amount_ -= 50;
    // acc2->amount_ += 50;
    // acc1.print();
}