#include <string>

class Account {
private:
    int amount_;
    std::string currency_;
    std::string name_;

public:
    Account(int amount, std::string currency, 
        std::string name): amount_(amount), 
        currency_(currency), name_(name) {};
    void print();
    int take(int amount, std::string currency);
    bool put(int amount, std::string currency);
};