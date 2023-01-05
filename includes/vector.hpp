/**
 * @file vector.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// std::allocator<T>
#include <memory>

namespace ft {

template <class T, class Allocator = std::allocator<T>>
class vector {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef reverse_iterator<iterator> reverse_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;

  // FUNCTION : push_back, insert, swap, erase, clear,
};

template <class T, class Allocator = std::allocator<T>>
bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <class T, class Allocator = std::allocator<T>>
bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <class T, class Allocator = std::allocator<T>>
bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <class T, class Allocator = std::allocator<T>>
bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <class T, class Allocator = std::allocator<T>>
bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <class T, class Allocator = std::allocator<T>>
bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);

template <class T, class Allocator = std::allocator<T>>
void swap(vector<T, Allocator>& x,
          vector<T, Allocator>& y) noexcept(noexcept(x.swap(y)));

}  // namespace ft

#endif  // VECTOR_HPP