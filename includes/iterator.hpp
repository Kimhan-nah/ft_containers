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
#include <deque>
#include <iterator>
#include <map>
#include <vector>

namespace ft {
// iterator_tags Iterator Tags
// struct input_iterator_tag {};
// struct output_iterator_tag {};
// struct forwward_iterator_tag : public input_iterator_tag {};
// struct bidirectional_iterator_tag : public forwward_iterator_tag {};
// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// iterator class (common iterator class)
template <typename Category, typename T, typename Distance = std::ptrdiff_t,
          typename Pointer = T *, typename Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

// SECTION 1. iterator_traits
template <typename Iter>
struct iterator_traits {
 public:
  // Member types
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

// template specialization <T *>
template <typename Tp>
struct iterator_traits<Tp *> {
 public:
  // Member type
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
  // Member type
  typedef std::ptrdiff_t difference_type;
  typedef typename ft::T value_type;
  typedef const typename T *pointer;
  typedef const typename T &reference;
  typedef std::random_access_iterator_tag iterator_category;
};
// !SECTION

// SECTION 2. reverse_iterator
template <typename Iter>
class reverse_iterator {
 public:
  // SECTION 2-1. Member types
  typedef Iter iterator_type;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::difference_type difference__type;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::reference reference;
  // !SECTION

  // SECTION 2-2. Member functions
  reverse_iterator();  // constructor
  reverse_iterator &operator=(const iterator &refreverse_);
  // !SECTION

  // SECTION 2-3. Member objects
  // TODO reverse_iterator's Member objects : current??
  // !SECTION
};

// SECTION 2-4. Non-member functions of reverse_iterator
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
// !SECTION
// !SECTION

}  // namespace ft
#endif