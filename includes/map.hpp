/**
 * @file map.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef MAP_HPP
#define MAP_HPP

#include <functional>  // std::less
#include <memory>      // std::allocator

#include "function.hpp"  // ft::select1st
#include "tree.hpp"      // ft::_rb_tree
#include "utility.hpp"   // ft::pair

namespace ft {

/**
 * @brief sorted associative container that contains key-value pairs
 *
 * @tparam Key map::key_type
 * @tparam T map::mapped_type
 * @tparam Compare map::key_compare
 * @tparam std::allocator<std::pair<const Key, T>>  map::allocator_type
 *
 * @note ft::pair<Key, T> -> value_type
 * 				==  ft::pair<key_type, mapped_type>
 * 				== value_type
 */
template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  // SECTION member types
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

  /**
   * @brief nested function class to compare elements
   */
  class value_compare : public binary_function<value_type, value_type, bool> {};

 private:
  // tree type
  typedef _rb_tree<key_type, value_type, ft::select1st<value_type>, key_compare, allocator_type>
      _rb_tree_type;

  // member object
  _rb_tree_type _m_tree;

  // !SECTION

 public:
  // SECTION Member functions
  // 1. constructors & Destructor
  // default constructor (empty)
  map(void) : _m_tree(key_compare(), allocator_type()) {}
  explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _m_tree(comp, alloc) {}

  // range
  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : _m_tree(comp, alloc) {
    // TODO first ~ last
  }

  // copy constructor
  map(const map& other) : _m_tree(other._m_tree) {}

  // destructor
  ~map(void) {}

  // operator=
  map& operator=(const map& other) {
    _m_tree = other._m_tree;
    return *this;
  }

  // get allocator
  allocator_type get_allocator(void) const;

  // 2. Element access
  value_type& at(const key_type key);
  const value_type& at(const key_type key) const;

  value__type& operator[](const key_type& key);

  // 3. Iterators
  iterator begin(void);
  const_iterator begin(void) const;

  iterator end(void);
  const_iterator end(void) const;

  reverse_iterator rbegin(void);
  const_reverse_iterator rbegin(void) const;

  reverse_iterator rend(void);
  const_reverse_iterator rend(void) const;

  // 4. Capacity
  bool empty(void) const;

  size_type size(void) const;
  size_type max_size(void) const;

  // 5. Modifiers
  // clear
  void clear(void);

  // insert - single element
  ft::pair<iterator, bool> insert(const value_type& val);
  // insert -with hint
  iterator insert(iterator position, const value_type& val);
  // insert - range
  template <class InputIter>
  void insert(InputIter first, InputIter last);

  // erase
  void erase(iterator position);
  size_type erase(const key_type& key);
  void erase(iterator first, iterator last);

  // swap
  void swap(map& other);

  // 6. Lookup
  // count
  size_type count(const key_type& key) const;

  // find
  iterator find(const key_type& key);
  const_iterator find(const key_type& k) const;

  /// equal_range
  ft::pair<iterator, iterator> equal_range(const key_type& key);
  ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

  // lower_bound
  iterator lower_bound(const key_type& key);
  const_iterator lower_bound(const key_type& key) const;

  // upper_bound
  iterator upper_bound(const key_type& key);
  const_iterator upper_bound(const key_type& key) const;

  // 7. Observers
  key_compare key_comp(void) const { return _m_tree.key_comp(); }
  value_compare value_comp(void) const {return value_compare(_m_tree.key_comp())};

  // !SECTION
};

// SECTION Non-member functions
// relational operators
// ==
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);

// !=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);

// <
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs);

// <=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);

// >
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs);

// >=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs);

// swap
template <class Key, class T, class Compare, class Alloc>
void swap(std::map<Key, T, Compare, Alloc>& lhs, std::map<Key, T, Compare, Alloc>& rhs);

}  // namespace ft
#endif