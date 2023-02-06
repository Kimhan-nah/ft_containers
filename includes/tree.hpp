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
template <typename Key, typename T>
class _rb_tree_iterator {};
// !SECTION

// SECTION rb_tree_base, rb_tree
template <typename Tp, typename Alloc>
class _rb_tree_base {};

// Rb_tree : protected Rb_tree_base<>
template <typename Key, typename Val, typename Compare, typename Alloc = std::allocator<Val> >
class _rb_tree : protected _rb_tree_Base<Val, Alloc> {
 private:
  typedef _rb_tree_base<Val, Alloc> _Base;

 public:
  typedef typename _Base::allocator_type allocator_type;
  typedef Key key_type;
  typedef Val value_type;

  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  typedef value_type& reference;
  typedef const value_type& const_reference;

  typedef _rb_tree_node* _Link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

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