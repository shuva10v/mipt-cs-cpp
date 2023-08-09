#include <atomic>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>

long counter1 = 0;
void increment_counter(long n) {
  for (long i = 0; i < n; i++) counter1 += 1;
};

void race_condition() {
  std::cout << "Counter before creating threads " << counter1 << "\n";
  std::thread t1(increment_counter, 1000000);
  std::thread t2(increment_counter, 1000000);
  std::cout << "Counter just after creating " << counter1 << "\n";
  t1.join();
  t2.join();
  std::cout << "Counter after join " << counter1 << "\n";
}

std::atomic<long> counter2{0};

void atomic_increment_counter(long n) {
  for (long i = 0; i < n; i++) counter2.fetch_add(1);
};

void atomic_increment() {
  std::cout << "Counter before creating threads " << counter2 << "\n";
  std::thread t1(atomic_increment_counter, 1000000);
  std::thread t2(atomic_increment_counter, 1000000);
  std::cout << "Counter just after creating " << counter2 << "\n";
  t1.join();
  t2.join();
  std::cout << "Counter after join " << counter2 << "\n";
}

long counter3 = 0;
std::mutex counter_mutex;

void increment_with_mutex(long n) {
  for (long i = 0; i < n; i++) {
    counter_mutex.lock();
    counter3 += 1;
    counter_mutex.unlock();
  }
};

void mutex_increment() {
  std::cout << "Counter before creating threads " << counter3 << "\n";
  std::thread t1(increment_with_mutex, 1000000);
  std::thread t2(increment_with_mutex, 1000000);
  std::cout << "Counter just after creating " << counter3 << "\n";
  t1.join();
  t2.join();
  std::cout << "Counter after join " << counter3 << "\n";
}

long counter4 = 0;

void increment_with_guard(long n) {
  for (long i = 0; i < n; i++) {
    std::lock_guard<std::mutex> lock(counter_mutex);
    counter4 += 1;
  }
};

void guard_increment() {
  std::cout << "Counter before creating threads " << counter4 << "\n";
  std::thread t1(increment_with_guard, 1000000);
  std::thread t2(increment_with_guard, 1000000);
  std::cout << "Counter just after creating " << counter4 << "\n";
  t1.join();
  t2.join();
  std::cout << "Counter after join " << counter4 << "\n";
}

class CounterHolder {
 private:
  std::atomic<long> counter_{0};

 public:
  void increment(long n) {
    for (long i = 0; i < n; i++) counter_.fetch_add(1);
  }
  long get() { return counter_.load(); };
  ~CounterHolder() { std::cout << "calling dtor\n"; };
};

void class_method() {
  auto counter = std::make_shared<CounterHolder>();
  std::cout << "Counter before creating threads " << counter->get() << "\n";
  std::thread t1(&CounterHolder::increment, counter, 1000000);
  std::thread t2(&CounterHolder::increment, counter, 1000000);
  std::cout << "Counter just after creating " << counter->get() << "\n";
  t1.join();
  t2.join();
  std::cout << "Counter after join " << counter->get() << "\n";
}

class MapHolder {
 private:
  std::map<int, std::string> map_;
  std::mutex mutex_;

 public:
  void put(std::string value, long n) {
    for (long i = 0; i < n; i++) {
      std::lock_guard<std::mutex> lock(mutex_);
      map_[i] = value;
    }
  }
  std::map<int, std::string> get() { return map_; };
  ~MapHolder() { std::cout << "calling dtor\n"; };
};

void map_concurrent_access() {
  auto map = std::make_shared<MapHolder>();
  std::thread t1(&MapHolder::put, map, "abc", 1000000);
  std::thread t2(&MapHolder::put, map, "def", 1000000);
  t1.join();
  t2.join();
  std::cout << "Map size after join " << map->get().size() << "\n";
}

int main() {
  // race_condition();
  // atomic_increment();
  // mutex_increment();
  // guard_increment();
  // class_method();
  map_concurrent_access();
}