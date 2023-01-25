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

namespace ft {
/** SECTION 0. vector_iterator
 * @brief random_access_iterator (normal_iterator in GNU)
 *
 * @tparam Iter	- the iterator type to retrieve properties for
 *
 * Iterator invalidation : swap, clear, operator=, assign, earse ...
 */
template <typename Iter>
struct vector_iterator {
 public:
  typedef Iter iterator_type;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::reference reference;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef
      typename ft::iterator_traits<Iter>::iterator_category iterator_category;

 protected:
  iterator_type _current;

 public:
  // SECTION constructor
  vector_iterator(void) : _current(iterator_type()) {}

  explicit vector_iterator(const iterator_type& it) : _current(it) {}

  // Allow iterator to const_iterator conversion
  template <typename _Iter>
  explicit vector_iterator(const vector_iterator<_Iter>& it)
      : _current(it.base()) {}

  // base()
  const iterator_type& base() const { return _current; }

  // destructor
  ~vector_iterator(void) {}

  // copy
  vector_iterator& operator=(const vector_iterator<>& other);

  // !SECTION

  // operator *, ->, [], ++, --, +, -, +=, -=
  reference operator*() const;

  // compare operators ==, !=, <. <=, >, >=

  // arithmetics operators +, -

  pointer base() const;
};

// TODO specialization
template <typename Iter>
struct vector_iterator<const Iter> {
 public:
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef typename ft::iterator_traits<Iter>::reference reference;
  typedef
      typename ft::iterator_traits<Iter>::iterator_category iterator_category;

  // TODO vector_iterator
  // vector_iterator() : iterator() {}
  // vector_iterator(const) {}
};
// !SECTION 0

}  // namespace ft
#endif