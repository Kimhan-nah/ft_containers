/**
 * @file iterator_traits.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

// std::ptrdiff_t
#include <cstddef>
// std::random_access_iterator_tag
#include <iterator>

namespace ft {

/** SECTION 0. iterator
 * @brief
 *
 * @tparam Category
 * @tparam T
 * @tparam Distance
 * @tparam Pointer - T*
 * @tparam Reference - T&
 */
template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T *,
          typename Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};
// !SECTION 0

/** SECTION 1. iterator_traits
 * @brief uniform interface to the properties of LegacyIterator types
 * 	LegacyIterator : Input, Output, Forward, Bidirectional, RandomAccess
 *
 * @tparam Iter - iterator
 */
template <typename Iter>
struct iterator_traits {
 public:
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

// template specialization <T *> for Array Pointer
template <typename Tp>
struct iterator_traits<Tp *> {
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef Tp *pointer;
  typedef Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

// template specialization <const T *>
template <typename Tp>
struct iterator_traits<const Tp *> {
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Tp value_type;
  typedef const Tp *pointer;
  typedef const Tp &reference;
  typedef std::random_access_iterator_tag iterator_category;
};
// !SECTION 1

/** SECTION 2. reverse_iterator
 * @brief iterator adaptor that reverses the direction of given iterator
 *
 * @tparam Iter - bidirectional iterator type || random-access iterator type
 */
template <typename Iter>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iter>::iterator_category,
                                             typename ft::iterator_traits<Iter>::value_type,
                                             typename ft::iterator_traits<Iter>::difference_type,
                                             typename ft::iterator_traits<Iter>::pointer,
                                             typename ft::iterator_traits<Iter>::reference> {
 public:
  typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef typename ft::iterator_traits<Iter>::reference reference;

  typedef Iter iterator_type;

 protected:
  /**
   * @brief Member objects
   * @note the underlying iterator of which base() returns a copy
   */
  iterator_type current;

  // SECTION 2-1. Member Functions
 public:
  // SECTION 2-1-1. (constructors)
  /* NOTE Exception Safety
   *	Provides the same level of guarantee as the proper constructor of the
   * 	base iterator
   */
  // 1. default
  reverse_iterator(void) : current() {}
  // 2. initialization
  // int *it
  reverse_iterator(iterator_type it) : current(it) {}
  // 3. copy / type-cast constructor
  template <typename _Iter>
  reverse_iterator(const reverse_iterator<_Iter> &rev_it) : current(rev_it.base()) {}

  // CHECK only cppreference.. there are no operaotr= in cplusplus and gcc code.
  // reverse_iterator tmp = *this;
  template <typename _Iter>
  reverse_iterator &operator=(const reverse_iterator<_Iter> &other) {
    // current(other.base());
    current = other.base();
    return *this;
  }

  /**
   * @brief accesses the underlying iterator
   * @exception same level of guarantee as the copy constructor of the base
   * iterator
   */
  iterator_type base(void) const { return current; }

  /**
   * @brief accesses the pointed-to element
   * @return the element previous to current
   */
  reference operator*(void) const {
    iterator_type tmp = current;
    return *--tmp;
  }

  /**
   * @brief accesses the pointed-to element
   * @return the element previous to current
   */
  pointer operator->(void) const { return &(operator*()); }

  /**
   * @brief accesses an element by index
   * @exception NO
   * @note element doesn't exist -> undefined behavior
   */
  reference operator[](difference_type n) const {
    // return *(current + n - 1); // right??
    return *(*this + n);  // operator+(n);
  }

  // advances or decrements the iterator
  reverse_iterator &operator++(void) {
    --current;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current;
    return tmp;
  }

  reverse_iterator &operator--(void) {
    ++current;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current;
    return tmp;
  }

  reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }

  reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }

  reverse_iterator &operator+=(difference_type n) {
    current -= n;
    return *this;
  }

  reverse_iterator &operator-=(difference_type n) {
    current += n;
    return *this;
  }
};
// !SECTION 2-1-1.

// SECTION 2-1-2. Non-member functions of reverse_iterator
/**
 * @brief Relational Operators (Compares the underlying iterators)
 * @note ==, !=, >, >=, <, <=
 * @param lhs left side iterator adator to compare
 * @param rhs right side iterator adaptor to compare
 */
// CHECK cplusplus & GCC -> both the same template parameter
// cppreference & LLVM -> different template parameter
template <typename IterL, typename IterR>
bool operator==(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename IterL, typename IterR>
bool operator!=(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() != rhs.base();
}

template <typename IterL, typename IterR>
bool operator>(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() < rhs.base();
}

template <typename IterL, typename IterR>
bool operator>=(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() <= rhs.base();
}

template <typename IterL, typename IterR>
bool operator<(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() > rhs.base();
}

template <typename IterL, typename IterR>
bool operator<=(const ft::reverse_iterator<IterL> &lhs, const ft::reverse_iterator<IterR> &rhs) {
  return lhs.base() >= rhs.base();
}

// operator+
// n + it
template <class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
                                 const reverse_iterator<Iter> &rev_it) {
  return reverse_iterator<Iter>(rev_it.base() - n);
}

// operator-
// rhs.base() - lhs.base()
template <class IterL, class IterR>
typename reverse_iterator<IterL>::difference_type operator-(const reverse_iterator<IterL> &lhs,
                                                            const reverse_iterator<IterR> &rhs) {
  return rhs.base() - lhs.base();
}

// !SECTION 2-1-2.
// !SECTION 2

}  // namespace ft
#endif