#include <iostream>
#include <map>
#include <memory>
#include <string>

class Chessman {
 private:
  std::string name_;

 protected:
  Chessman(std::strig name) : name_(name){};

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
  ChessmanRegistry() {
    add("pawn", Pawn::create);
    add("bishop", Bishop::create);
  };
};
