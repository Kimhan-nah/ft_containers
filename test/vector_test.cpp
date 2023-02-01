// #include "../includes/vector.hpp"

#include <iostream>
#include <vector>

int main(void) {
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