#include <iostream>
#include <vector>

int main() {
  std::vector<int> v1;

  v1.push_back(3);
  v1.push_back(4);
  v1.push_back(5);
  v1.push_back(6);
  v1.push_back(7);
  v1.push_back(8);

  for (std::vector<int>::iterator mysweetiterator = v1.begin();
       mysweetiterator != v1.end(); mysweetiterator++)
    std::cout << *mysweetiterator << std::endl;
  return 0;
}