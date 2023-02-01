/**
 * @file type_traits.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

// SECTION enable_if
template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};
// !SECTION

#endif