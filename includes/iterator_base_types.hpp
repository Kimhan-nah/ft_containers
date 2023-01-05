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

#ifndef ITERATOR_BASE_TYPES_HPP
#define ITERATOR_BASE_TYPES_HPP

// std::ptrdiff_t
#include <cstddef>

namespace ft {
// iterator_tags Iterator Tags
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forwward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forwward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// common iterator class
template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {  // why struct????? not class???
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

// iterator_traits ????????
template <class Iter>
class iterator_traits {
 public:
  // Member types
  typedef Iter::difference_type difference_type;
  typedef Iter::value_type value_type;
  typedef Iter::pointer pointer;
  typedef Iter::reference reference;
  typedef Iter::iterator_category iterator_category;
};

// template specialization
template <class T>
class iterator_traits {
 public:
  // Member type
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

}  // namespace ft
#endif