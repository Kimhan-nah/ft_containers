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

// SECTION 1. vector
template <typename T, typename Allocator = std::allocator<T>>
class vector {
 public:
  // SECTION 1-1. Member types
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  // TODO Modify iterator & conts_iterator
  // LegacyRandomAccessIterator and LegacyContiguousIterator to value_type
  typedef asdf iterator;
  typedef asdf const_iterator;

  typedef reverse_iterator<iterator> reverse_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  // !SECTION

  // SECTION 1-2. Member Functions [element access/iterators/capacity/modifiers]
  // Canonical class form
  vector();
  ~vector();
  vector& operator=(const vector& ref);
  // assign
  // get_allocator

  // Element access

  // Iterators

  // Capacity

  // Modifiers
  // !SECTION
};
// !SECTION

// SECTION 2. Non-member functions
template <typename T, typename Allocator = std::allocator<T>>
bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <typename T, typename Allocator = std::allocator<T>>
bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <typename T, typename Allocator = std::allocator<T>>
bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <typename T, typename Allocator = std::allocator<T>>
bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <typename T, typename Allocator = std::allocator<T>>
bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);
template <typename T, typename Allocator = std::allocator<T>>
bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y);

template <typename T, typename Allocator = std::allocator<T>>
void swap(vector<T, Allocator>& x,
          vector<T, Allocator>& y) noexcept(noexcept(x.swap(y)));
// !SECTION

// SECTION 3. vector_iterator : random_access_iterator (normal_iterator in GNU)
// Iterator invalidation : swap, clear, operator=, assign, earse ...
template <typename _Iter, typename Container>
struct vector_iterator {
 public:
  // Member type
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;

  // iterator
  vector_iterator() : iterator() {}
  vector_iterator(const)
};
// !SECTION

}  // namespace ft

#endif  // VECTOR_HPP