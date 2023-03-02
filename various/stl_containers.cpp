#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

class User {
 private:
  int i_;

 public:
  User(int i) : i_(i){};
  void print() const { std::cout << "User #" << i_ << "\n"; };
  bool operator<(const User& rhs) const { return this->i_ < rhs.i_; };
};

class Book {
 private:
  int year_;
  std::string title_;

 public:
  Book(std::string title, int year) : title_(title), year_(year){};
  Book(){};
  Book(const Book& src) : Book(src.title_, src.year_){};
  friend std::ostream& operator<<(std::ostream& s, const Book& book) {
    return s << book.title_ << ", " << book.year_;
  }
};

int main() {
  std::list<std::string> c_list;
  c_list.push_back("body");
  c_list.push_back("tail");
  c_list.push_front("head");

  std::cout << "Iterating over list (iterator-based):\n";
  for (std::list<std::string>::iterator it = c_list.begin(); it != c_list.end();
       ++it) {
    std::cout << *it << "\n";
  }

  std::cout << "Iterating over list (iterator-based) with auto:\n";
  for (auto it = c_list.begin(); it != c_list.end(); ++it) {
    std::cout << *it << "\n";
  }

  std::cout << "Iterating over list (range-for loop):\n";
  for (const std::string& item : c_list) {
    std::cout << item << "\n";
  }

  std::cout << "Iterating over list (range-for loop) with auto:\n";
  for (const auto& item : c_list) {
    std::cout << item << "\n";
  }

  // dynamic size
  std::vector<int> c_vector;
  c_vector.push_back(2);
  c_vector.insert(c_vector.begin(), 1);
  // doesn't work
  // c_vector[2] = 3;
  c_vector.push_back(3);
  c_vector[2] = 55;
  std::cout << "Iterating over vector:\n";
  for (const auto& item : c_vector) {
    std::cout << item << "\n";
  }

  // pre-allocate
  std::vector<int> c_vector_fixed(3);
  c_vector_fixed[0] = 1;
  c_vector_fixed[1] = 2;
  c_vector_fixed.push_back(4);
  std::cout << "Iterating over vector:\n";
  for (const auto& item : c_vector_fixed) {
    std::cout << item << "\n";
  }

  std::set<User> users;
  users.insert(User(22));
  std::cout << "Set size: " << users.size() << "\n";
  users.insert(User(23));
  users.insert(User(21));
  std::cout << "Set size: " << users.size() << "\n";
  users.insert(User(21));
  std::cout << "Set size: " << users.size() << "\n";
  users.begin()->print();
  (--users.end())->print();
  std::cout << "User(223): " << (users.find(User(223)) != users.end()) << "\n";
  std::cout << "User(22): " << (users.find(User(22)) != users.end()) << "\n";
  users.erase(users.find(User(22)));
  std::cout << "Set size: " << users.size() << "\n";
  std::cout << "User(22): " << (users.find(User(22)) != users.end()) << "\n";

  std::map<std::string, Book> books;
  books.emplace("Leo Tolstoy", Book("War and peace", 1869));
  books.emplace("Ken Kesey", Book("One Flew Over the Cuckoo's Nest", 1962));
  // default and copy construcor required!
  books["Charles Bukowski"] = Book("Post Office", 1971);
  for (const auto& [key, value] : books) {
    std::cout << value << " by " << key << "\n";
  }

  std::cout << books["Leo Tolstoy"] << "\n";
  books.erase("Leo Tolstoy");
  // dangerous!
  std::cout << books["Leo Tolstoy"] << "\n";
  // throws std::out_of_range
  try {
    std::cout << books.at("George Orwell") << "\n";
  } catch (std::out_of_range e) {
    std::cerr << "No such entry!\n";
  }

  // pair
  std::pair<int, std::string> pair{12, "aaa"};
  std::cout << pair.first << ": " << pair.second << "\n";

  std::map<std::string, std::string> routes{{"Moscow", "Rostov"},
                                            {"Khabarovsk", "Novosibirsk"}};
  for (const auto& [key, value] : routes) {
    std::cout << value << " <=> " << key << "\n";
  }

  std::list<int> ints({1, 1, 3, 4, 5});

  // algorithms
  std::cout << "Number of ones: " << std::count(ints.begin(), ints.end(), 1)
            << "\n";
  std::vector<int> tosort({6, 5, 3, 3, 4, 5});
  std::sort(tosort.begin(), tosort.end());
  for (auto item : tosort) {
    std::cout << item << "\n";
  }

  auto minmax = std::minmax_element(ints.begin(), ints.end());
  std::cout << "Min: " << *(minmax.first) << ", Max: " << *(minmax.second)
            << "\n";

  // working with strings
  std::string s("my string");
  // raw data access
  printf(s.c_str());
  std::cout << "\n";

  std::cout << "2nd char is '" << s[2] << "'\n";
  s.insert(0, "op-op:");
  std::cout << s << "\n";
  std::cout << "string token position: " << s.find("string") << "\n";
  std::cout << (s + " tail") << "\n";
  return 0;
}