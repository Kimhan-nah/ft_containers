/**
 * @file tree.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TREE_HPP
#define TREE_HPP

// std::allocator<T>
#include <memory>
// std::bidirectional_iterator:tag
#include <iterator>
// std::ptrdiff_t, std::size_t
#include <cstddef>

// reverse_iterator
#include "iterator.hpp"

namespace ft {
enum _rb_tree_color { RED = false, BLACK = true };

// SECTION node_base, node
struct _rb_tree_node_base {
  // typedef _rb_tree_node_base* _base_ptr;

  // member object
  _rb_tree_color _m_color;
  _rb_tree_node_base* _m_parent;
  _rb_tree_node_base* _m_left;
  _rb_tree_node_base* _m_right;

  // init
  // _rb_tree_node_base() {
  //   _m_color = RED;
  //   _m_parent = NULL;
  //   _m_left = NULL;
  //   _m_right = NULL;
  // }

  // minimum
  // maximum
};

// Rb_tree_node : Rb_tree_node_base
template <typename Val>
struct _rb_tree_node : public _rb_tree_node_base {
  typedef _rb_tree_node<Val>* _link_type;

  // member object
  Val _m_value_field;
};
// !SECTION node

// SECTION iterator
template <typename Val, typename Ref, typename Ptr>
struct _rb_tree_iterator {
  typedef Val value_type;
  typedef Ref reference;
  typedef Ptr pointer;

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  // member object
  _rb_tree_node_base* _m_node;

  // Constructors
  _rb_tree_iterator(void) {}
  _rb_tree_iterator(_rb_tree_iterator* x) { _m_node = x; }
  _rb_tree_iterator(const _rb_tree_iterator& other) : _m_node(other._m_node) {}

  // destructor
  ~_rb_tree_iterator(void) {}

  // operator=
  _rb_tree_iterator operator=(const _rb_tree_iterator& other) {
    _m_node = other._m_node;
    return *this;
  }

  reference operator*(void) const { return _rb_tree_node(_m_node)->value; }
  pointer operator->(void) const;

  _rb_tree_iterator& operator++(void);
  _rb_tree_iterator operator++(void);

  _rb_tree_iterator& operator--(void);
  _rb_tree_iterator operator--(void);
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
}

// !SECTION

// SECTION rb_tree_base, rb_tree
template <typename Tp, typename Alloc>
class _rb_tree_base {};

// Rb_tree : protected Rb_tree_base<>
template <typename Key, typename Val, typename KeyOfValue, typename Compare,
          typename Alloc = std::allocator<Val> >
class _rb_tree : protected _rb_tree_Base<Val, Alloc> {
 private:
  typedef _rb_tree_base<Val, Alloc> _Base;

  //  protected:
  // 	typedef _rb_tree_node<Val> _rb_tree_node;

 public:
  typedef typename _Base::allocator_type allocator_type;
  typedef Key key_type;    // std::string, ...
  typedef Val value_type;  // int, ...
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _rb_tree_node<value_type>* _link_type;  // node<int>*
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  // _rb_tree_iterator<int, int&,  int*>
  typedef _rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  // default constructor
  _rb_tree(void) : _Base(allocator_type()) {}

  // copy constructor

  // destructor
  ~_rb_tree(void) { clear(); }

  // operator=
  _rb_tree<>& operator=(const _rb_tree<>& other) {}
};
// !SECTION

}  // namespace ft

#endif