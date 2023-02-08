#include "bank.h"
#include <iostream>

// Account::Account(int amount, std::string currency, std::string name) {
//     this->amount_ = amount;
//     this->currency_ = currency;
//     this->name_ = name;
// }

void Account::print() {
    std::cout << this->name_ << " " <<
     this->amount_ << " " << this->currency_ << std::endl;
}

int Account::take(int amount, std::string currency) {
    if (amount > this->amount_) {
        std::cerr << "No funds" << std::endl;
        return 0;
    }
    if (currency != this->currency_) {
        std::cerr << "Wrong currency" << std::endl;
        return 0;
    }
    this->amount_ -= amount;
    return amount;
}

bool Account::put(int amount, std::string currency) {
    if (currency != this->currency_) {
        return false;
    }
    this->amount_ += amount;
    return true;
}
