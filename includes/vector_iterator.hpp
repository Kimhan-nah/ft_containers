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

#include "iterator"

/** SECTION 0. vector_iterator
 * @brief random_access_iterator (normal_iterator in GNU)
 *
 * @tparam Iter
 * @tparam Container
 *
 * Iterator invalidation : swap, clear, operator=, assign, earse ...
 */
template <typename Iter>
struct vector_iterator {
  // CHECK Consider inherit iterator_traits to vector_iterator
 public:
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;

  // TODO modify vector_iterator constructor
  // vector_iterator() : iterator() {}
  // vector_iterator(const) {}
};

// specialization
template <typename Iter>
struct vector_iterator<const Iter> {
 public:
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;

  // TODO vector_iterator
  // vector_iterator() : iterator() {}
  // vector_iterator(const) {}
};
// !SECTION 0

#endif