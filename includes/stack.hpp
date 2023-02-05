/**
 * @file stack.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template <typename T, typename Container = ft::vector<T> >
class stack {
 public:
  // typedef T value_type;
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

 protected:
  // Member objects
  container_type _m_cont;

 public:
  // SECTION Member functions
  // 1. constructor & destructor
  explicit stack(const container_type& cont = container_type())
      : _m_cont(cont) {}
  // CHECK copy constructor doesn't needed
  // stack(const stack& other) : _m_cont(cont) {}

  // CHECK only cppreference
  ~stack(void) {}

  stack& operator=(const stack& other) {
    _m_cont = other._m_cont;
    return *this;
  }

  // 2. Element access
  reference top(void) { return _m_cont.back(); }
  reference top(void) const { return _m_cont.back(); }

  // 3. Capacity
  bool empty(void) const { return _m_cont.empty(); }
  size_type size(void) const { return _m_cont.size(); }

  // 4. Modifiers
  void push(const value_type& value) { _m_cont.push_back(value); }
  void pop(void) { _m_cont.pop_back(); }

  // friend declaration for access to the protected member object 'c'
  template <typename _T, typename _Container>
  friend bool operator==(const ft::stack<_T, _Container>& lhs,
                         const ft::stack<_T, _Container>& rhs);

  template <typename _T, typename _Container>
  friend bool operator<(const ft::stack<_T, _Container>& lhs,
                        const ft::stack<_T, _Container>& rhs);
  // !SECTION
};

// SECTION Non-member functions
// == (friend function)
template <typename T, typename Container>
bool operator==(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return lhs._m_cont == rhs._m_cont;
}

// !=
template <typename T, typename Container>
bool operator!=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

// < (friend function)
template <typename T, typename Container>
bool operator<(const ft::stack<T, Container>& lhs,
               const ft::stack<T, Container>& rhs) {
  return lhs._m_cont < rhs._m_cont;
}

// <=
template <typename T, typename Container>
bool operator<=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return !(rhs < lhs);
}

// >
template <typename T, typename Container>
bool operator>(const ft::stack<T, Container>& lhs,
               const ft::stack<T, Container>& rhs) {
  return rhs < lhs;
}

// >=
template <typename T, typename Container>
bool operator>=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return !(lhs < rhs);
}
// !SECTION

}  // namespace ft

#endif