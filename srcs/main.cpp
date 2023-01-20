#include <iostream>
#include <vector>

#include "iterator.hpp"
#include "vector.hpp"

int main() {
  // std::vector<int> v1;

  // v1.push_back(3);
  // v1.push_back(4);
  // v1.push_back(5);
  // v1.push_back(6);
  // v1.push_back(7);
  // v1.push_back(8);

  // for (std::vector<int>::iterator mysweetiterator = v1.begin();
  //      mysweetiterator != v1.end(); mysweetiterator++)
  //   std::cout << *mysweetiterator << std::endl;

  typedef std::vector<int> IntVec;
  IntVec v;
  v.reserve(5);

  for (int i = 1; i <= 5; i++) {
    v.push_back(i);
  }

  // IntVec::reverse_iterator ri = find(v.begin(), v.end(), 3);

  // IntVec::iterator base(ri.base());
  return 0;
}