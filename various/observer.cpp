#include <iostream>
#include <list>
#include <memory>

// abstract class
class Observer {
 public:
  virtual void notify(const std::string&) = 0;
};

class LoggingObserver : public Observer {
 public:
  void notify(const std::string& value) {
    std::cout << "Got notification: " << value << "\n";
  }
};

class LongestStrObserver : public Observer {
 private:
  std::string longest_;

 public:
  LongestStrObserver() : longest_(""){};
  const std::string& longest() { return longest_; };
  void notify(const std::string& value) {
    if (value.length() > longest_.length()) {
      longest_ = value;
    }
  }
};

class ObserverManager {
 public:
  void registerObserver(std::shared_ptr<Observer> o) {
    observers_.push_back(o);
  }

  void handle(const std::string& value) {
    for (auto observer : observers_) {
      observer->notify(value);
    }
  }

 private:
  std::list<std::shared_ptr<Observer>> observers_;
};

int main() {
  std::cout << "Running observer example\n";
  ObserverManager manager = ObserverManager();
  manager.registerObserver(std::shared_ptr<Observer>(new LoggingObserver()));
  auto longest = std::shared_ptr<LongestStrObserver>(new LongestStrObserver());
  manager.registerObserver(longest);
  manager.handle("test1");
  manager.handle("test2");
  manager.handle("test2dsds");
  std::cout << "Longest str: " << longest->longest() << "\n";
  return 0;
}