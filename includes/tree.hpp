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

#include <cstddef>     // std::ptrdiff_t, std::size_t
#include <functional>  // std::less
#include <memory>      // std::allocator<T>

#include "function.hpp"       // ft::select1st
#include "iterator.hpp"       // ft::reverse_iterator
#include "tree_iterator.hpp"  // ft::map_iterator
#include "utility.hpp"        // ft::pair

namespace ft {
enum _rb_tree_color { RED = false, BLACK = true };

/** SECTION node_base
 * @brief pointer(parent, left, right), NO value
 */
class _rb_tree_node_base {
 public:
  typedef _rb_tree_node_base* base_ptr;  // value access X

  // member object
  _rb_tree_color _m_color;
  base_ptr _m_parent;
  base_ptr _m_left;
  base_ptr _m_right;

  // constructor
  _rb_tree_node_base(void) : _m_color(RED), _m_parent(NULL), _m_left(NULL), _m_right(NULL) {}
};
// !SECTION

/** SECTION node
 * @brief included value(needed template parameter)
 */
template <typename Val>
class _rb_tree_node : public _rb_tree_node_base {
 public:
  typedef Val value_type;
  typedef _rb_tree_node<value_type>* link_type;  // value access O

  // member object
  value_type _m_value_field;  // Val == ft::pair<key_type, mapped_type> == {key, value}

  // constructor
  _rb_tree_node(const value_type& value) : _m_value_field(value) {}

  // copy constructor
  _rb_tree_node(const _rb_tree_node<value_type>& other) : _m_value_field(other._m_value_field) {}
};
// !SECTION node

// SECTION rb_tree_base
/**
 * @brief Base class to encapsulate the differences
 * @note manage node memory using allocator
 *
 * @tparam Val
 * @tparam Alloc
 */
template <typename Val, typename Alloc = std::allocator<Val> >
class _rb_tree_base {
 protected:
  typedef Val value_type;
  // typedef Alloc allocator_type;
  typedef _rb_tree_node<value_type>* link_type;
  typedef typename Alloc::template rebind<_rb_tree_node<value_type> >::other node_allocator;

  // member object
  node_allocator _m_alloc;
  _rb_tree_node_base _m_header;  // tree header

  // constructor
  _rb_tree_base(const node_allocator& alloc = node_allocator())
      : _m_alloc(alloc), _m_header(_m_alloc.allocate(1)) {}

  // get_node_allocator
  node_allocator get_node_allocator(void) const { return _m_alloc; }

  // allocate new node
  link_type allocate_node(void) { return _m_alloc.allocate(1); }

  // deallocate node
  void deallocate_node(_rb_tree_node<value_type>* p) { _m_alloc.deallocate(p, 1); }
};
// !SECTION

// SECTION rb_tree
/**
 * @brief  RB_Tree
 *
 * @tparam Key - key type
 * @tparam Val - ft::pair<key_type, mapped_type>
 * @tparam KeyOfValue - functor
 * @tparam Compare - compare function
 * @tparam Alloc
 */
template <typename Key, typename Val, typename KeyOfValue = ft::select1st<Val>,
          typename Compare = std::less<Key>, typename Alloc = std::allocator<Val> >
class _rb_tree : protected _rb_tree_base<Val, Alloc> {
  // tree_base
 private:
  typedef _rb_tree_base<Val, Alloc> _Base;
  typedef _rb_tree<Key, Val, Compare, Alloc> _self;

 public:
  typedef Key key_type;
  typedef Val value_type;
  typedef Compare key_compare;
  typedef typename _Base::node_allocator node_allocator;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  // iterator
  typedef _rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // node
 protected:
  typedef _rb_tree_node_base* base_ptr;
  typedef _rb_tree_node<value_type> rb_tree_node;
  typedef rb_tree_node* link_type;

 protected:
  using _Base::_m_alloc;
  using _Base::_m_header;
  using _Base::allocate_node;
  using _Base::deallocate_node;

  size_type _m_node_count;
  key_compare _m_key_compare;

 public:
  // constructor
  _rb_tree(const key_compare& comp = key_compare(), const node_allocator& alloc = node_allocator())
      : _Base(alloc), _m_node_count(0), _m_key_compare(comp) {}

  // TODO copy constructor
  _rb_tree(const _self& other)
      : _Base(other.get_node_allocator()), _m_node_count(0), _m_key_compare(other._m_key_compare) {
    if (other._root() == NULL) {
      // _initialize_header();
    } else {
      _m_header._m_color = RED;
      _root() = _copy_tree(other._root(), _header());
      // _root() = _copy_tree(other._root(), _root());
      _leftmost() = other._leftmost();
      _rightmost() = other._rightmost();
      // _m_header._m_left = other._m_header._m_left;
      // _m_header._m_right = other._m_header._m_right;
    }
    _m_node_count = other._m_node_count;
  }

  // destructor
  ~_rb_tree(void) { clear(); }

  // operator=
  _self& operator=(const _self& other) {
    if (this != other) {
      clear();
      _m_node_count = 0;
      _m_key_compare = other._m_key_compare;
      if (other._root() == NULL) {
        _m_header._m_parent = NULL;
      } else {
        _m_header._m_parent = other._m_header._m_parent;
      }
    }
    return *this;
  }

 public:
  // SECTION public functions (map)
  // get allocator
  node_allocator get_node_allocator(void) const { return _Base::get_node_allocator(); }

  // 2. Element access
  value_type& at(const key_type key);
  const value_type& at(const key_type key) const;

  value_type& operator[](const key_type& key);

  // 3. Iterators
  iterator begin(void) { return iterator(_m_header._m_left); }
  const_iterator begin(void) const { return const_iterator(_m_header._m_left); }

  iterator end(void) { return iterator(_m_header); }
  const_iterator end(void) const { return const_iterator(_m_header); }

  reverse_iterator rbegin(void) { return reverse_iterator(end()); }
  const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }

  reverse_iterator rend(void) { return reverse_iterator(begin()); }
  const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

  // 4. Capacity
  bool empty(void) const { return _m_node_count == 0; }

  size_type size(void) const { return _m_node_count; }
  size_type max_size(void) const { return _m_alloc.max_size(); }

  // 5. Modifiers
  // clear
  void clear(void) {}

  // insert - single element
  ft::pair<iterator, bool> insert(const value_type& val) {
    link_type loc = _root();           // root
    link_type loc_parent = _header();  // header
    bool is_left = true;

    // find position
    while (loc != NULL) {
      loc_parent = loc;
      is_left = _m_key_compare(KeyOfValue()(val), _get_key(loc));
      loc = is_left ? _left(loc) : _right(loc);
    }

    iterator iter(loc_parent);

    if (is_left) {  // comp가 true인 경우 == 마지막에 왼쪽으로 내려온 경우
      // insert left
      if (iter == begin()) {                                              // if there are no root
        return ft::pair<iterator, bool>(_insert(loc_parent, val), true);  // make root
      } else {
        --iter;
      }
    }

    // check duplicated key
    if (_m_key_compare(_get_key(iter._m_node), KeyOfValue()(val))) {
      return ft::pair<iterator, bool>(_insert(loc_parent, val), true);
    }
    return ft::pair<iterator, bool>(iter, false);
  }

  // insert - with hint
  iterator insert(iterator position, const value_type& val);

  // insert - range
  template <typename InputIter>
  void insert(InputIter first, InputIter last);

  // erase
  void erase(iterator position);
  size_type erase(const key_type& key);
  void erase(iterator first, iterator last);

  // swap
  void swap(_self& other);

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
  key_compare key_comp(void) const { return _m_key_compare; }

  // !SECTION

  // SECTION private functions (node)
 private:
  link_type _root(void) const { return static_cast<link_type>(_m_header._m_parent); }

  // get header
  link_type _header(void) const {
    // return static_cast<link_type>(_m_header);
    return static_cast<link_type>(end()._m_node);
  }

  value_type _get_value(const link_type node) const { return node->_m_value_field; }

  key_type _get_key(const link_type node) const { return KeyOfValue()(_get_value(node)); }

  link_type _left(base_ptr& node) const { return static_cast<link_type>(node->_m_left); }

  link_type _right(base_ptr& node) const { return static_cast<link_type>(node->_m_right); }

  link_type _parent(base_ptr& node) const { return static_cast<link_type>(node->_m_parent); }

  link_type _leftmost(void) const { return static_cast<link_type>(_m_header._m_left); }

  link_type _rightmost(void) const { return static_cast<link_type>(_m_header._m_right); }

  link_type _create_node(const value_type& value) {
    link_type tmp = allocate_node();

    _m_alloc.construct(tmp->_m_value_field, value);
    return tmp;
  }

  link_type _clone_node(const link_type other) {
    link_type tmp = _create_node(other->_m_value_field);

    tmp->_m_color = other->_m_color;
    tmp->_m_left = NULL;
    tmp->_m_right = NULL;

    return tmp;
  }

  void _destroy_node(link_type p) {
    _m_alloc.destroy(p->_m_value_field);
    deallocate_node(p);
  }

  // void _initialize_header(void) {
  // 	_m_alloc.construct();

  //   _m_header._m_color = RED;
  //   _m_header._m_parent = NULL;
  //   _m_header._m_left = NULL;
  //   _m_header._m_right = NULL;
  // }

  // TODO _M_copy()
  link_type _copy_tree(link_type src, link_type dst) {
    link_type top = _clone_node(src);
    top->_m_parent = dst;

    if (src->_m_right) {
      top->_m_right = _copy_tree(_right(src), top);
    }
    dst = top;
    src = _left(src);
  }

  /**
   * @brief 실질적으로 rb_tree insert가 이루어짐 (with rebalancing)
   *
   * @param _parent point to location of parent
   * @param value value of node to insert
   * @return iterator
   */
  iterator _insert(base_ptr _parent, const value_type& value) {
    link_type parent = static_cast<link_type>(_parent);
    link_type new_node;

    new_node = _create_node(val);

    if (parent == _header || _m_key_compare(KeyOfValue()(val), _get_key(parent))) {
      _left(parent) = new_node;

      if (parent == _header) {             // there are no root
        _root() = new_node;                // make root
        _rightmost() = new_node;           // _right(parent) = new_node;
      } else if (parent == _leftmost()) {  // update leftmost
        _leftmost() = new_node;
      }
    } else {
      _right(parent) = new_node;
      if (parent == _rightmost()) {
        _rightmost() = new_node;
      }
    }
    // set parent of new_node
    _parent(new_node) = parent;

    _rebalance_rb_tree(new_node);
    ++_m_node_count;

    return iterator(new_node);
  }
  // !SECTION
};
// !SECTION

// SECTION Non-member function
void _rebalance_rb_tree(base_ptr* x) {}

}  // namespace ft

#endif