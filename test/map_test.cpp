#include "map.hpp"

#include <stdlib.h>

#include <iostream>
#include <map>
#include <string>

#include "utility.hpp"

void _print(ft::map<int, std::string>::iterator begin, ft::map<int, std::string>::iterator end) {
  std::cout << "--- print tree ---\n";
  for (; begin != end; ++begin) {
    std::cout << (*begin).first << ", " << (*begin).second << std::endl;
  }
  std::cout << std::endl;
}

#include <cstdlib>
#include <ctime>

int main() {
  {
    typedef ft::map<int, std::string> map_type;
    std::cout << "=== ft::_rb_tree test ===" << std::endl;

    map_type test;
    test[2] = "second";
    test[1] = "first";
    test[3] = "third";
    map_type::iterator iter = test.find(3);
    // test.insert(iter, ft::make_pair(4, "!!!"));

    for (int i = 0; i < 16; i++) {
      int tmp = std::rand() % 16;
      std::cout << "insert : " << tmp;
      test.insert(ft::make_pair(tmp, "dummy value"));
      // test.insert(iter, ft::make_pair(tmp, "dummy value"));
      std::cout << std::endl;
    }
    _print(test.begin(), test.end());

    system("leaks a.out");
  }

  // {
  //   std::cout << "==== std::map test ====" << std::endl;

  //   // map<key_type, mapped_typ>
  //   std::map<std::string, int> ages;
  //   ages["John"] = 25;
  //   ages["Jane"] = 30;
  //   ages["Jim"] = 35;

  //   std::cout << "John is " << ages["John"] << " years old." << std::endl;
  //   std::cout << "Jane is " << ages["Jane"] << " years old." << std::endl;
  //   std::cout << "Jim is " << ages["Jim"] << " years old." << std::endl;
  // }
  // {
  //   std::cout << "==== std::pair, std::make_pair test ====" << std::endl;
  //   // Using std::pair to create a pair of values
  //   std::pair<int, std::string> person1(30, "John");
  //   std::cout << "Age: " << person1.first << ", Name: " << person1.second << std::endl;

  //   // Using std::make_pair to create a pair of values
  //   std::pair<int, std::string> person2 = std::make_pair(25, "Jane");
  //   std::cout << "Age: " << person2.first << ", Name: " << person2.second << std::endl;
  // }
  // {
  //   std::cout << "=== std::map test ===" << std::endl;

  //   std::map<std::string, int> map1;
  //   // map1["key"] = 1;

  //   std::cout << "map1[key] : " << map1["key"] << std::endl;

  //   // map1.insert(std::pair<double, int>(123.123, 12345));
  //   map1.insert(std::pair<std::string, int>("a", 12345));
  //   // std::cout << "map1[\"a\"] : " << map1["a"] << std::endl;
  // }

  return 0;
}
