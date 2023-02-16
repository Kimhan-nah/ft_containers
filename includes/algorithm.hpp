/**
 * @file algorithm.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 * @note equal, lexicographical_compare, swap
 */
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {
// SECTION equal
/**
 * @brief equality version
 * @note using operator==
 */
template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

// predicate version
/**
 * @brief predicate version
 * @note using binary predicate function
 *
 * @param pred  bool cmp(const Type1 &a, const Type2 &b);
 */
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!pred(*first1, *first2)) {
      return false;
    }
  }
  return true;
}
// !SECTION

// SECTION lexicographical_compare
/**
 * @brief default version
 * @note using operator<
 */
template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }

  return (first1 == last1) && (first2 != last2);
}

/**
 * @brief custom version
 * @note using binary comparison function comp
 *
 * @param comp bool cmp(const Type1 &a, const Type2 &b);
 */
template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                             Compare comp) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
  }

  return (first1 == last1) && (first2 != last2);
}

// !SECTION

// SECTION swap
template <typename T>
void _swap(T& a, T& b) {
  T tmp(a);
  a = b;
  b = tmp;
}

// template <typename Tp>
// void _swap(Tp& a, Tp& b) {
//   Tp tmp = a;
//   a = b;
//   b = tmp;
// }

}  // namespace ft

#endif