/**
 * @file utility.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023
 * @note std::pair(class template), std::make_pair(function template)
 */
#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
// SECTION pair
template <typename T1, typename T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  // member variables
  first_type first;
  second_type second;

  // constructors
  // default
  pair(void) : first(), second() {}

  // copy
  template <typename U1, typename U2>
  pair(const pair<U1, U2>& other) : first(other.first), second(other.second) {}

  // initialization
  pair(const first_type& a, const second_type& b) : first(a), second(b) {}

  // operator=
  pair& operator=(const pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  }
};

// SECTION Non-member functions
// NOTE relational operators, make_pair

// SECTION relational operators
template <class T1, class T2>
bool operator==(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs);

// !SECTION relational operators

/** SECTION make_pair
 * @brief creates a ft::pair object
 *
 * @tparam T1
 * @tparam T2
 * @param t
 * @param u
 * @return pair<T1, T2>
 */
template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 t, T2 u);
// !SECTION make_pair

// !SECTION pair

}  // namespace ft

#endif