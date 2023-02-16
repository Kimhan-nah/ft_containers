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
          typename Alloc = std::allocator<ft::pair<Key, T> > >
class map {
 public:
  // SECTION member types
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<key_type, mapped_type> value_type;
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
  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map<Key, T, Compare, Alloc>;

   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

 private:
  typedef _rb_tree<key_type, value_type, ft::select1st<value_type>, key_compare, allocator_type>
      _rb_tree_type;
  _rb_tree_type _m_tree;

 public:
  typedef typename _rb_tree_type::iterator iterator;
  typedef typename _rb_tree_type::const_iterator const_iterator;
  typedef typename _rb_tree_type::reverse_iterator reverse_iterator;
  typedef typename _rb_tree_type::const_reverse_iterator const_reverse_iterator;
  // !SECTION

 public:
  // SECTION Member functions
  // 1. constructors & Destructor
  // default constructor (empty)
  map(void) : _m_tree(key_compare(), allocator_type()) {}
  explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type())
      : _m_tree(comp, alloc) {}

  // range
  template <typename InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const allocator_type& alloc = allocator_type())
      : _m_tree(comp, alloc) {
    _m_tree.insert_unique(first, last);
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
  allocator_type get_allocator(void) const { return _m_tree.get_node_allocator(); }

  // 2. Element access
  /**
   * @brief Returns a reference to the mapped value of the element with key equivalent to key. If
   * no such element exists, an exception of type std::out_of_range is thrown. CHECK It is not
   * C++98. is it C++11??
   */
  mapped_type& at(const key_type key) {
    iterator iter = find(key);
    if (iter == end()) {
      throw std::out_of_range("ft::map::at");
    }
    return iter->second;
  }
  const mapped_type& at(const key_type key) const {
    const_iterator iter = find(key);
    if (iter == end()) {
      throw std::out_of_range("ft::map::at");
    }
    return iter->second;
  }

  /**
   * @brief find key, if there are no the key, insert new
   */
  mapped_type& operator[](const key_type& key) {
    // tree_iterator
    iterator iter = find(key);
    if (iter == end()) {
      iter = insert(value_type(key, mapped_type())).first;
    }
    return iter->second;
  }

  // 3. Iterators
  iterator begin(void) { return _m_tree.begin(); }
  const_iterator begin(void) const { return _m_tree.begin(); }

  iterator end(void) { return _m_tree.end(); }
  const_iterator end(void) const { return _m_tree.end(); }

  reverse_iterator rbegin(void) { return _m_tree.rbegin(); }
  const_reverse_iterator rbegin(void) const { return _m_tree.rbegin(); }

  reverse_iterator rend(void) { return _m_tree.rend(); }
  const_reverse_iterator rend(void) const { return _m_tree.rend(); }

  // 4. Capacity
  bool empty(void) const { return _m_tree.empty(); }

  size_type size(void) const { return _m_tree.size(); }
  size_type max_size(void) const { return _m_tree.max_size(); }

  // 5. Modifiers
  // clear
  void clear(void) { _m_tree.clear(); }

  // insert - single element
  ft::pair<iterator, bool> insert(const value_type& val) { return _m_tree.insert_unique(val); }
  // insert_unique -with hint
  iterator insert(iterator position, const value_type& val) {
    return _m_tree.insert_unique(position, val);
  }
  // insert - range
  template <class InputIter>
  void insert(InputIter first, InputIter last) {
    _m_tree.insert_unique(first, last);
  }

  // erase
  void erase(iterator position) { _m_tree.erase(position); }
  size_type erase(const key_type& key) { return _m_tree.erase(key); }
  void erase(iterator first, iterator last) { _m_tree.erase(first, last); }

  // swap
  void swap(map& other) { _m_tree.swap(other._m_tree); }

  // 6. Lookup
  // count
  size_type count(const key_type& key) const { return _m_tree.count(key); }

  // find
  iterator find(const key_type& key) { return _m_tree.find(key); }
  const_iterator find(const key_type& key) const { return _m_tree.find(key); }

  /// equal_range
  ft::pair<iterator, iterator> equal_range(const key_type& key) { return _m_tree.equal_range(key); }
  ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
    return _m_tree.equal_range(key);
  }

  // lower_bound
  iterator lower_bound(const key_type& key) { return _m_tree.lower_bound(key); }
  const_iterator lower_bound(const key_type& key) const { return _m_tree.lower_bound(key); }

  // // upper_bound
  iterator upper_bound(const key_type& key) { return _m_tree.upper_bound(key); }
  const_iterator upper_bound(const key_type& key) const { return _m_tree.upper_bound(key); }

  // 7. Observers
  key_compare key_comp(void) const { return _m_tree.key_comp(); }
  value_compare value_comp(void) const { return value_compare(_m_tree.key_comp()); }

  // operator==, operator<
  template <typename _Key, typename _T, typename _Comp, typename _Alloc>
  friend bool operator==(const map<_Key, _T, _Comp, _Alloc>& lhs,
                         const map<_Key, _T, _Comp, _Alloc>& rhs);

  template <typename _Key, typename _T, typename _Comp, typename _Alloc>
  friend bool operator<(const map<_Key, _T, _Comp, _Alloc>& lhs,
                        const map<_Key, _T, _Comp, _Alloc>& rhs);

  // !SECTION
};

// SECTION Non-member functions
// relational operators
// ==
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return lhs._m_tree == rhs._m_tree;
}

// !=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs == rhs);
}

// <
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return lhs._m_tree < rhs._m_tree;
}

// <=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(rhs < lhs);
}

// >
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
  return rhs < lhs;
}

// >=
template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
  return !(lhs < rhs);
}

// swap
template <class Key, class T, class Compare, class Alloc>
void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft
#endif