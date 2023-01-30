// erasing from vector
#include <iostream>
#include <vector>

int main() {
  std::vector<int> myvector;
  std::vector<int>::iterator iter;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++) myvector.push_back(i);

  // erase the 6th element
  iter = myvector.erase(myvector.begin() + 5);  // 1 2 3 4 5 7 8 9 10
  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  std::cout << "return iterator : " << *iter << "\n==========\n" << std::endl;

  // erase the first 3 elements:
  iter = myvector.erase(myvector.begin(), myvector.begin() + 3);  //

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  std::cout << "return iterator : " << *iter << "\n==========\n" << std::endl;

  // erase the last element -> segmentation fault!
  iter = myvector.erase(myvector.begin() + 2, myvector.end());

  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  std::cout << "return iterator : " << *iter << "\n==========\n" << std::endl;

  // insert return test
  iter = myvector.insert(myvector.end() + 1, 42);
  std::cout << "insert return : " << *iter << std::endl;
  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << "\n====\n\n";

  // iter = myvector.insert(myvector.begin(), 2, 4242);
  // std::cout << "insert return : " << *iter << std::endl;
  // std::cout << "myvector contains:";
  // for (unsigned i = 0; i < myvector.size(); ++i)
  //   std::cout << ' ' << myvector[i];
  // std::cout << "\n====\n\n";

  return 0;
}