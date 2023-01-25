// #include "../includes/vector.hpp"

#include <iostream>
#include <vector>

int main(void) {
  std::cout << "===== vector test =====" << std::endl;

  std::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++) myvector.push_back(i);

  // throw exceptioni
  myvector.at(10);

  // erase the 6th element
  myvector.erase(myvector.begin() + 5);

  // erase the first 3 elements:
  myvector.erase(myvector.begin(), myvector.begin() + 3);

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}