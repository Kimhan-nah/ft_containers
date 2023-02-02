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

int main() {
  catch_type<void>();
  catch_type<int>();

  return 0;
}