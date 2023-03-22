#include <iostream>

struct Container {
  std::string name;
  Container(std::string name_arg) : name(name_arg){};
};

void implicit_cast() {
  int a = 100;
  long b = a;
  std::cout << "a = " << a << ", b = " << b << "\n";
  std::string s = "value";
  Container c = s;
  std::cout << "c.name = " << c.name << "\n";
};

class Parent {
  std::string value = "parent";

 public:
  const std::string say() { return "I am parent (" + value + ")"; };
  //   virtual void hi(){};
};

class Child : public Parent {
  // std::string value = "secret";
  std::string value = "child";

 public:
  const std::string say() { return "I am child (" + value + ")"; };
};

void explicit_cast() {
  int a = 100;
  long b = (long)a;
  std::cout << "a = " << a << ", b = " << b << "\n";
  Child* c = new Child();
  Parent* p = (Parent*)c;
  std::cout << "p says " << p->say() << "\n";
  std::cout << "c says " << c->say() << "\n";
  delete c;

  p = new Parent();
  c = (Child*)p;
  std::cout << "p says " << p->say() << "\n";
  std::cout << "c says " << c->say() << "\n";
  delete p;
}

void dynamic_cast_() {
  Child* c = new Child();
  Parent* p = dynamic_cast<Parent*>(c);

  std::cout << "p says " << p->say() << "\n";
  std::cout << "c says " << c->say() << "\n";
  delete c;

  // Only makes sense for polymorhic classes, i.e. with virtual methods
  //   p = new Parent();
  //   c = dynamic_cast<Child*>(p);

  //   if (c == nullptr) {
  //     std::cout << "nullptr\n";
  //     return;
  //   }
  //   std::cout << "p says " << p->say() << "\n";
  //   std::cout << "c says " << c->say() << "\n";
  //   delete p;
}

void static_cast_() {
  Child* c = new Child();
  Parent* p = static_cast<Parent*>(c);

  std::cout << "p says " << p->say() << "\n";
  std::cout << "c says " << c->say() << "\n";
  delete c;

  p = new Parent();
  c = static_cast<Child*>(p);

  if (c == nullptr) {
    std::cout << "nullptr\n";
    return;
  }
  std::cout << "p says " << p->say() << "\n";
  std::cout << "c says " << c->say() << "\n";
  delete p;
}

void reinterpret_cast_() {
  Child* c = new Child();
  // with static_cast you'll get error: invalid 'static_cast' from type 'Child*'
  // to type 'const char*'
  const char* p = reinterpret_cast<const char*>(c);

  std::cout << "p text " << p << "\n";
  delete c;
}

void const_cast_() {
  const Child* c = new Child();
  Child* c2 = const_cast<Child*>(c);

  std::cout << "c says " << c2->say() << "\n";
  delete c;
}

int main() {
  implicit_cast();
  //   explicit_cast();
  //   dynamic_cast_();
  //   static_cast_();
  // reinterpret_cast_();
  //   const_cast_();
}