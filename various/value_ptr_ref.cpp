#include <iostream>

class Counter {
 private:
  int i_;

 public:
  Counter() : i_(0){};
  // adding const allows to call print on const instance of Counter
  void print() const { std::cout << "Value is " << i_ << "\n"; };
  void inc() { i_++; };
};

void f_inc(Counter* c) { c->inc(); };
void f_inc(Counter c) { c.inc(); };
void f_inc_ref(Counter& c) { c.inc(); };
void f_print_const(const Counter& c) { c.print(); };

int main() {
  Counter* c1 = new Counter();
  c1->print();
  c1->inc();
  c1->print();
  f_inc(c1);

  c1->print();
  f_inc(*c1);

  c1->print();
  f_inc_ref(*c1);
  c1->print();
  f_print_const(*c1);
  delete c1;
}