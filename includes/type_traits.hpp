/**
 * @file type_traits.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 * @note enalbe_if, is_integral
 */
#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

// #include <type_traits>

namespace ft {
// SECTION 1. enable_if
/**
 * @brief B가 false인 경우 typedef 없음
 */
template <bool B, typename T = void>
struct enable_if {};

/**
 * @brief true일 경우 typedef
 */
template <typename T>
struct enable_if<true, T> {
  typedef T type;
};
// !SECTION

// SECTION 2. integral_constant for is_integral
template <typename T, T v>
struct integral_constant {
  // member constant
  static const T value = v;

  // member type
  typedef T value_type;
  typedef integral_constant<T, v> type;

  // member function
  operator value_type(void) const { return value; }
};

// specializations
typedef ft::integral_constant<bool, true> true_type;
typedef ft::integral_constant<bool, false> false_type;
// !SECTION

// SECTION 3. is_integral

template <typename T>
struct is_integral : public false_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

template <>
struct is_integral<short> : public true_type {};

template <>
struct is_integral<unsigned short> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<long> : public true_type {};

template <>
struct is_integral<unsigned long> : public true_type {};

template <>
struct is_integral<long long> : public true_type {};

template <>
struct is_integral<unsigned long long> : public true_type {};
// !SECTION

// template <class InputIter>
// struct is_input_iterator
//     : public integral_constant<
//           bool,
//           std::is_base_of<input_iterator_tag,
//                           iterator_traits<Iter>::iterator_category>::value>
//                           {};

// is_same

}  // namespace ft

#endif