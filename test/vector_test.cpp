// #include "../includes/vector.hpp"

#include <iostream>
#include <vector>

int main(void) {
  std::cout << "===== vector test =====" << std::endl;

  std::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++) myvector.push_back(i);

  // throw exception
  // myvector.at(10);

  // erase the 6th element
  myvector.erase(myvector.begin() + 5);

  // erase the first 3 elements:
  myvector.erase(myvector.begin(), myvector.begin() + 3);

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  // test resize
  myvector.resize(3, 0);
  std::cout << "after resize(3,0) :";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  // std::cout << myvector.capacity() << std::endl;

  myvector.resize(myvector.capacity() + 5, 42);
  std::cout << "after resize(capacity() + 5, 42) :";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.resize(10, 4242);
  std::cout << "after resize(10, 4242) :";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  std::cout << "capacity : " << myvector.capacity() << std::endl;
  std::cout << "size : " << myvector.size() << std::endl;

  // insert return test
  std::vector<int>::iterator iter;

  iter = myvector.insert(myvector.begin() + 1, -123);
  std::cout << "insert return : " << *iter << std::endl;
  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << "\n====\n\n";

  return 0;
}