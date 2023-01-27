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
// std::iterator, std::random_access_iterator_tag
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
template <typename Category, typename T, typename Distance = std::ptrdiff_t,
          typename Pointer = T *, typename Reference = T &>
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
class reverse_iterator
    : public ft::iterator<typename iterator_traits<Iter>::iterator_category,
                          typename iterator_traits<Iter>::value_type,
                          typename iterator_traits<Iter>::difference_type,
                          typename iterator_traits<Iter>::pointer,
                          typename iterator_traits<Iter>::reference> {
 public:
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::reference reference;

  typedef Iter iterator_type;

 protected:
  /**
   * @brief Member objects
   * @note the underlying iterator of which base() returns a copy
   */
  iterator_type _current;

  // SECTION 2-1. Member Functions
 public:
  // SECTION 2-1-1. (constructors)
  /* NOTE Exception Safety
   *	Provides the same level of guarantee as the proper constructor of the
   * 	base iterator
   */
  // 1. default
  reverse_iterator(void) : _current(void) {}
  // 2. initialization
  explicit reverse_iterator(iterator_type it) : _current(it) {}
  // 3. copy / type-cast constructor
  template <typename _Iter>
  reverse_iterator(const reverse_iterator<_Iter> &rev_it)
      : _current(rev_it.base()) {}

  // CHECK only cppreference.. there are no operaotr= in cplusplus and gcc code.
  template <typename _Iter>
  reverse_iterator &operator=(const reverse_iterator<_Iter> &other)
      : _current(other.base()) {
    return *this;
  }

  /**
   * @brief accesses the underlying iterator
   * @exception same level of guarantee as the copy constructor of the base
   * iterator
   */
  iterator_type base(void) const { return _current; }

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
    // return *(_current + n - 1); // right??
    return *(*this + n);  // operator+(n);
  }

  // advances or decrements the iterator
  reverse_iterator &operator++(void) {
    --_current;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --_current;
    return tmp;
  }

  reverse_iterator &operator--(void) {
    ++_current;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++_current;
    return tmp;
  }
  reverse_iterator operator+(difference_type n) const;
  reverse_iterator operator-(difference_type n) const;
  reverse_iterator &operator+=(difference_type n);
  reverse_iterator &operator-=(difference_type n);
};

// SECTION 2-1. Non-member functions of reverse_iterator
/*
// TODO reverse-iterator Non-member functions
        operator==
        operator!=
        operator<
        operator<=
        operator>
        operator>=

        operator+
        operator-
*/
// !SECTION 2-1
// !SECTION 2

}  // namespace ft
#endif