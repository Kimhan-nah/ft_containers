#include <iostream>
#include <type_traits>

template <typename _Tp>
void catch_type(typename std::enable_if<std::is_void<_Tp>::value>::type* = 0) {
  if (std::is_void<_Tp>::value) {
    std::cout << "void" << std::endl;
  } else {
    std::cout << "not void" << std::endl;
  }
}

// template <typename _Tp>
// void catch_type(_Tp* = 0) {
//   if (std::is_void<_Tp>::value) {
//     std::cout << "void" << std::endl;
//   } else {
//     std::cout << "not void" << std::endl;
//   }
// }
template <typename T>
class Base {
 public:
  typedef int myint;
  int x;
};

template <typename T>
class Derived : public Base<T> {
 public:
  int y;

  // void doSomething() { this->x = 5; }
  void doSomething() { typename Base<T>::myint a = 5; }
};

int main() {
  catch_type<void>();
  Derived<int> a;
  a.doSomething();
  // std::cout << "a.x : " << a.x << std::endl;
  // catch_type<int>();

  return 0;
}