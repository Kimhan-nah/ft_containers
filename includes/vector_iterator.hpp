/**
 * @file vector_iterator.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-01-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>

#include "iterator"
#include "type_traits.hpp"

namespace ft {
/** SECTION 0. vector_iterator
 * @brief random_access_iterator (normal_iterator in GNU)
 *
 * @tparam Iter - ft::vector::pointer(T*)
 *
 */
template <typename Iter>
struct vector_iterator {
 public:
  typedef Iter iterator_type;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::reference reference;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;

 protected:
  iterator_type current;

 public:
  // SECTION constructor
  vector_iterator(void) : current(iterator_type()) {}

  // copy constructor
  vector_iterator(const iterator_type& other) : current(other) {}

  // Allow iterator to const_iterator conversion
  // const copy constructor (non-const -> const)
  template <typename _Iter>
  vector_iterator(const vector_iterator<_Iter>& other) : current(other.base()) {}

  // base()
  // CHECK return const iterator_type&?? (reverse_iterator base)
  const iterator_type& base(void) const { return current; }

  ~vector_iterator(void) {}

  // CHECK operator=
  template <typename _Iter>
  vector_iterator& operator=(const vector_iterator<_Iter>& other) {
    current = other.base();
    return *this;
  }

  // !SECTION

  // SECTION operators
  // operator *, ->, [], ++, --, +, -, +=, -=
  reference operator*(void) const { return *current; }
  pointer operator->(void) const { return current; }
  reference operator[](difference_type n) const { return current[n]; }

  // ++iter
  vector_iterator& operator++(void) {
    ++current;
    return *this;
  }
  // iter++
  vector_iterator operator++(int) { return vector_iterator(current++); }

  // --iter
  vector_iterator& operator--(void) {
    --current;
    return *this;
  }
  // iter--
  vector_iterator operator--(int) { return vector_iterator(current--); }

  // iter + n, iter - n
  vector_iterator operator+(const difference_type& n) const { return vector_iterator(current + n); }
  vector_iterator operator-(const difference_type& n) const { return vector_iterator(current - n); }

  vector_iterator& operator+=(const difference_type& n) {
    current += n;
    return *this;
  }
  vector_iterator& operator-=(const difference_type& n) {
    current -= n;
    return *this;
  }
  // !SECTION
};
// !SECTION 0. vector_iterator

// SECTION 1. compare operators ==, !=, <. <=, >, >=
template <typename IterL, typename IterR>
bool operator==(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() == rhs.base();
}

template <typename IterL, typename IterR>
bool operator!=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() != rhs.base();
}

template <typename IterL, typename IterR>
bool operator<(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() < rhs.base();
}

template <typename IterL, typename IterR>
bool operator<=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() <= rhs.base();
}

template <typename IterL, typename IterR>
bool operator>(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() > rhs.base();
}

template <typename IterL, typename IterR>
bool operator>=(const vector_iterator<IterL>& lhs, const vector_iterator<IterR>& rhs) {
  return lhs.base() >= rhs.base();
}
// !SECTION 1

// SECTION 2. arithmetics operators +, -
// a + n, a - n => member function
// n + a, n - a => Non-member function
// a - b				=> Non-member function

/**
 * @brief n + iterator
 * @return vector_iterator<Iter>
 */
template <typename Iter>
vector_iterator<Iter> operator+(const typename vector_iterator<Iter>::difference_type& n,
                                const vector_iterator<Iter>& iter) {
  return vector_iterator<Iter>(iter.base() + n);
}

/**
 * @brief n - iterator
 * @return vector_iterator<Iter>
 */
template <typename Iter>
vector_iterator<Iter> operator-(const typename vector_iterator<Iter>::difference_type& n,
                                const vector_iterator<Iter>& iter) {
  return vector_iterator<Iter>(n - iter.base());
}

/**
 * @brief iterator - iterator
 * @param lhs left-iterator
 * @param rhs right-iterator
 * @return difference_type
 */
template <typename IterL, typename IterR>
typename vector_iterator<IterL>::difference_type operator-(const vector_iterator<IterL>& lhs,
                                                           const vector_iterator<IterR>& rhs) {
  return lhs.base() - rhs.base();
}
// !SECTION

}  // namespace ft
#endif