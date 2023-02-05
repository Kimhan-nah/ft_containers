#include <iostream>
#include <map>
#include <string>

int main() {
  {
    std::cout << "==== std::map test ====" << std::endl;

    std::map<std::string, int> ages;
    ages["John"] = 25;
    ages["Jane"] = 30;
    ages["Jim"] = 35;

    std::cout << "John is " << ages["John"] << " years old." << std::endl;
    std::cout << "Jane is " << ages["Jane"] << " years old." << std::endl;
    std::cout << "Jim is " << ages["Jim"] << " years old." << std::endl;
  }
  {
    std::cout << "==== std::pair, std::make_pair test ====" << std::endl;
    // Using std::pair to create a pair of values
    std::pair<int, std::string> person1(30, "John");
    std::cout << "Age: " << person1.first << ", Name: " << person1.second
              << std::endl;

    // Using std::make_pair to create a pair of values
    std::pair<int, std::string> person2 = std::make_pair(25, "Jane");
    std::cout << "Age: " << person2.first << ", Name: " << person2.second
              << std::endl;
  }

  return 0;
}
