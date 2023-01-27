#include <iostream>
#include <iterator>
#include <vector>

int main(void) {
  std::vector<int> myvector;
  for (int i = 0; i < 10; i++) myvector.push_back(i + 1);

  std::vector<int>::iterator from(myvector.begin());
  std::vector<int>::iterator until(myvector.end());

  std::reverse_iterator<std::vector<int>::iterator> rev_until(from);
  std::reverse_iterator<std::vector<int>::iterator> rev_from(until);

  // std::cout << "myvector : ";
  // while (from != until) {
  //   std::cout << ' ' << *from;
  //   from++;
  // }
  std::cout << *from << std::endl;
  --from;
  std::cout << *from << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  // std::cout << "--from : " << *--from << std::endl;
  // std::cout << "--from : " << *--from << std::endl;

  // std::cout << "reverse myvector : ";
  // while (rev_from != rev_until) {
  //   std::cout << ' ' << *rev_from++;
  // }

  // std::cout << std::endl;

  // from -= 3;
  // std::reverse_iterator<std::vector<int>::iterator> rev(from);

  // std::cout << "from : " << *from << std::endl;
  // std::cout << "rev : " << *rev << std::endl;
  // std::cout << std::endl;

  // rev++;
  // std::cout << "from : " << *from << std::endl;
  // std::cout << "rev : " << *rev << std::endl;
  // std::cout << std::endl;

  return 0;
}