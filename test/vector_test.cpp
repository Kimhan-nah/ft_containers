// #include "../includes/vector.hpp"

#include "vector.hpp"

#include <iostream>
#include <vector>

// #define T_SIZE_TYPE typename ft::vector<T>::size_type

template <typename T>
void printSize(ft::vector<T> const &vct, bool print_content = true) {
  // T_SIZE_TYPE typename ft::vector<T>::size_type
  const typename ft::vector<T>::size_type size = vct.size();
  const typename ft::vector<T>::size_type capacity = vct.capacity();
  const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
  // Cannot limit capacity's max value because it's implementation dependent

  std::cout << "size: " << size << std::endl;
  std::cout << "capacity: " << isCapacityOk << std::endl;
  std::cout << "max_size: " << vct.max_size() << std::endl;
  if (print_content) {
    typename ft::vector<T>::const_iterator it = vct.begin();
    typename ft::vector<T>::const_iterator ite = vct.end();
    std::cout << std::endl << "Content is:" << std::endl;
    for (; it != ite; ++it) std::cout << "- " << *it << std::endl;
  }
  std::cout << "###############################################" << std::endl;
}

int main(void) {
  {
    std::cout << "==== assign test ====" << std::endl;
    ft::vector<int> vct(7);
    ft::vector<int> vct_two(4);
    ft::vector<int> vct_three;
    ft::vector<int> vct_four;

    for (unsigned long int i = 0; i < vct.size(); ++i)
      vct[i] = (vct.size() - i) * 3;
    for (unsigned long int i = 0; i < vct_two.size(); ++i)
      vct_two[i] = (vct_two.size() - i) * 5;
    printSize(vct);
    printSize(vct_two);

    vct_three.assign(vct.begin(), vct.end());
    vct.assign(vct_two.begin(), vct_two.end());
    vct_two.assign(2, 42);
    vct_four.assign(4, 21);

    std::cout << "\t### After assign(): ###" << std::endl;

    printSize(vct);
    printSize(vct_two);
    printSize(vct_three);
    printSize(vct_four);

    vct_four.assign(6, 84);
    printSize(vct_four);

    std::cout << "\t### assign() on enough capacity and low size: ###"
              << std::endl;

    vct.assign(5, 53);
    vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

    printSize(vct);
    printSize(vct_two);
  }
  {
    std::cout << "==== erase test ==== " << std::endl;

    std::vector<int> myvector;

    for (int i = 0; i < 10; i++) myvector.push_back(i + 1);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  {
    std::cout << "===== resize test ====" << std::endl;

    std::vector<int> myvector;

    for (int i = 0; i < 10; i++) myvector.push_back(i + 1);

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
  }

  {
    std::cout << "===== insert test =====" << std::endl;

    std::vector<int> myvector;

    for (int i = 0; i < 10; i++) myvector.push_back(i + 1);
    // insert return test
    std::vector<int>::iterator iter;

    iter = myvector.insert(myvector.begin() + 1, -123);
    std::cout << "insert return : " << *iter << std::endl;
    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i)
      std::cout << ' ' << myvector[i];
    std::cout << "\n====\n\n";
  }

  {
    std::cout << "===== swap test ======" << std::endl;

    std::vector<int> myvector;
    for (int i = 0; i < 10; i++) myvector.push_back(i + 1);

    std::vector<int> tmp;
    for (int i = 0; i < 3; i++) {
      tmp.push_back(100 + i);
    }

    // before swap
    // print myvector
    std::cout << "Before swap()" << std::endl;
    std::cout << "myvector size : " << myvector.size() << std::endl;
    std::cout << "myvector capacity : " << myvector.capacity() << std::endl;
    for (int i = 0; i < myvector.size(); i++) {
      std::cout << myvector[i] << " ";
    }
    std::cout << std::endl;

    // print tmp vector
    std::cout << "tmp size : " << tmp.size() << std::endl;
    std::cout << "tmp capacity : " << tmp.capacity() << std::endl;
    for (int i = 0; i < tmp.size(); i++) {
      std::cout << tmp[i] << " ";
    }
    std::cout << std::endl << std::endl;

    // swap()
    myvector.swap(tmp);
    // std::swap(myvector, tmp);

    // after swap
    // print myvector
    std::cout << "After swap()" << std::endl;
    std::cout << "myvector size : " << myvector.size() << std::endl;
    std::cout << "myvector capacity : " << myvector.capacity() << std::endl;
    for (int i = 0; i < myvector.size(); i++) {
      std::cout << myvector[i] << " ";
    }
    std::cout << std::endl;

    // print tmp vector
    std::cout << "tmp size : " << tmp.size() << std::endl;
    std::cout << "tmp capacity : " << tmp.capacity() << std::endl;
    for (int i = 0; i < tmp.size(); i++) {
      std::cout << tmp[i] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}