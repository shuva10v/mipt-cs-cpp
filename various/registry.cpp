#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>

class Chessman {
 private:
  std::string name_;

 protected:
  Chessman(std::string name) : name_(name){};

 public:
  std::string name() { return name_; };
};

class Pawn : public Chessman {
 public:
  Pawn() : Chessman("pawn"){};
  ~Pawn() { std::cout << "Pawn dtor\n"; };
  static std::shared_ptr<Chessman> create() { return std::make_shared<Pawn>(); }
};

class Bishop : public Chessman {
 public:
  Bishop() : Chessman("bishop"){};
  ~Bishop() { std::cout << "Bishop dtor\n"; };
  static std::shared_ptr<Chessman> create() {
    return std::make_shared<Bishop>();
  }
};

class ChessmanRegistry {
 public:
  static ChessmanRegistry& getInstance() {
    static ChessmanRegistry s;
    return s;
  }
  // disable copy in any form
  ChessmanRegistry(ChessmanRegistry&) = delete;
  ChessmanRegistry& operator=(const ChessmanRegistry&) = delete;

  using factoryFunction = std::function<std::shared_ptr<Chessman>()>;
  void add(const std::string& name, factoryFunction factory) {
    registry_[name] = factory;
  };

  std::shared_ptr<Chessman> create(const std::string& name) {
    if (registry_.find(name) == registry_.end()) {
      return nullptr;
    }
    auto factory = registry_[name];
    return factory();
  }

 private:
  std::map<std::string, factoryFunction> registry_;
  ChessmanRegistry(){};
};

int main() {
  std::cout << "Running registry example\n";
  ChessmanRegistry::getInstance().add("pawn", Pawn::create);

  std::shared_ptr<Chessman> pawn =
      ChessmanRegistry::getInstance().create("pawn");
  std::shared_ptr<Chessman> bishop =
      ChessmanRegistry::getInstance().create("bishop");
  // std::shared_ptr<Chessman> bishop = Chessman::create(BISHOP);
  std::cout << "I am pawn: " << pawn->name() << "\n";
  if (bishop) {
    std::cout << "I am bishop: " << bishop->name() << "\n";
  } else {
    std::cout << "Bishop not registered!\n";
  }

  ChessmanRegistry::getInstance().add("bishop", Bishop::create);
  bishop = ChessmanRegistry::getInstance().create("bishop");
  if (bishop) {
    std::cout << "I am bishop: " << bishop->name() << "\n";
  } else {
    std::cout << "Bishop not registered!\n";
  }
  return 0;
}