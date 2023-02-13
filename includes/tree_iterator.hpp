/**
 * @file tree_iterator.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <cstddef>   // std::ptrdiff_t, std::size_t
#include <iterator>  // std::bidirectional_iterator:tag

#include "tree.hpp"

namespace ft {

// SECTION iterator
template <typename Val, typename Ref, typename Ptr>
struct _rb_tree_iterator {
  typedef Val value_type;
  typedef Ref reference;
  typedef Ptr pointer;

  // typedef typename ft::_rb_tree_node_base::base_ptr base_ptr;
  typedef ft::_rb_tree_node_base* base_ptr;
  typedef ft::_rb_tree_node<Val>* link_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  typedef _rb_tree_iterator<Val, Ref, Ptr> _self;

  // member object
  base_ptr _m_node;

  // Constructor
  _rb_tree_iterator(void) {}

  // node_base constructor
  _rb_tree_iterator(base_ptr node) : _m_node(node) {}

  // Copy Constructor
  _rb_tree_iterator(const _self& other) : _m_node(other._m_node) {}

  // destructor
  ~_rb_tree_iterator(void) {}

  // operator=
  _rb_tree_iterator operator=(const _rb_tree_iterator& other) {
    _m_node = other._m_node;
    return *this;
  }

  reference operator*(void) const { return static_cast<link_type>(_m_node)->_m_value_field; }
  pointer operator->(void) const { return &(static_cast<link_type>(_m_node)->_m_value_field); }

  _self& operator++(void) {
    increment();
    return *this;
  }
  _self operator++(int) {
    _self tmp = *this;
    increment();
    return tmp;
  }

  _self& operator--(void) {
    decrement();
    return *this;
  }
  _self operator--(int) {
    _self tmp = *this;
    decrement();
    return tmp;
  }

  void increment(void) {
    if (_m_node->_m_right != NULL) {
      _m_node = _m_node->_m_right;
      while (_m_node->_m_left != NULL) {
        _m_node = _m_node->_m_left;
      }
    } else {  // InOrder L-ROOT-R
      base_ptr parent = _m_node->_m_parent;

      while (_m_node == parent->_m_right) {
        _m_node = parent;
        parent = parent->_m_parent;
      }
      // if (_m_node != root)
      if (_m_node != _m_node->_m_parent) _m_node = parent;
    }
  }

  void decrement(void) {
    if (_m_node->_m_left != NULL) {
      _m_node = _m_node->_m_left;
      while (_m_node->_m_right != NULL) {
        _m_node = _m_node->_m_right;
      }
    } else {
      base_ptr parent = _m_node->_m_parent;

      while (_m_node == parent->_m_left) {
        _m_node = parent;
        parent = parent->_m_parent;
      }
      _m_node = parent;
    }
  }
};
// Non-member function
// ==
template <typename Val, typename Ref, typename Ptr>
bool operator==(const _rb_tree_iterator<Val, Ref, Ptr>& lhs,
                const _rb_tree_iterator<Val, Ref, Ptr>& rhs) {
  return lhs._m_node == rhs._m_node;
}

// !=
template <typename Val, typename Ref, typename Ptr>
bool operator!=(const _rb_tree_iterator<Val, Ref, Ptr>& lhs,
                const _rb_tree_iterator<Val, Ref, Ptr>& rhs) {
  return lhs._m_node != rhs._m_node;
};

// !SECTION

}  // namespace ft

#endif