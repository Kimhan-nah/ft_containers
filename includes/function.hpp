/**
 * @file function.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <functional>

namespace ft {

// template <class Operation>
// class binder1st : public unary_function<typename Operation::second_argument_type,
//                                         typename Operation::result_type> {
//  protected:
//   Operation op;
//   typename Operation::first_argument_type value;

//  public:
//   binder1st(const Operation& x, const typename Operation::first_argument_type& y)
//       : op(x), value(y) {}

//   typename Operation::result_type operator()(
//       const typename Operation::second_argument_type& x) const {
//     return op(value, x);
//   }
// };

template <class _Pair>
struct select1st : public std::unary_function<_Pair, typename _Pair::first_type> {
  typename _Pair::first_type& operator()(_Pair& __x) const { return __x.first; }
  const typename _Pair::first_type& operator()(const _Pair& __x) const { return __x.first; }
};

template <class _Pair>
struct select2nd : public std::unary_function<_Pair, typename _Pair::second_type> {
  typename _Pair::second_type& operator()(_Pair& __x) const { return __x.second; }
  const typename _Pair::second_type& operator()(const _Pair& __x) const { return __x.second; }
};

}  // namespace ft

#endif