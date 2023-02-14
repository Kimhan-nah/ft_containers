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
#include <iostream>    // TODO delete this
#include <iterator>    // std::bidirectional_iterator_tag
#include <memory>      // std::allocator<T>

#include "function.hpp"  // ft::select1st
#include "iterator.hpp"  // ft::reverse_iterator
#include "utility.hpp"   // ft::pair

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

// SECTION iterator
template <typename Val, typename Ref, typename Ptr>
struct _rb_tree_iterator {
  typedef Val value_type;
  typedef Ref reference;
  typedef Ptr pointer;

  typedef _rb_tree_node_base::base_ptr base_ptr;
  typedef ft::_rb_tree_node<Val>* link_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  typedef _rb_tree_iterator<Val, Ref, Ptr> _self;

  // member object
  base_ptr _m_node;  // iterator

  // Constructor
  _rb_tree_iterator(void) {}

  // node_base constructor
  _rb_tree_iterator(const base_ptr node) : _m_node(node) {}

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
      // if (_m_node->_m_right != parent) _m_node = parent;
    }
  }

  void decrement(void) {
    if (_m_node->_m_color == RED && _m_node->_m_parent->_m_parent == _m_node) {  // header?
      _m_node = _m_node->_m_right;

    } else if (_m_node->_m_left != NULL) {  // left != NULL => 자식
      _m_node = _m_node->_m_left;
      while (_m_node->_m_right != NULL) {  // 자식의 오른쪽 자식이 있는지 확인
        _m_node = _m_node->_m_right;
      }
    } else {  // left == NULL => 부모로 올라가서 찾아야 함
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
  _rb_tree_base(const node_allocator& alloc = node_allocator()) : _m_alloc(alloc) {}

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
      : _Base(alloc), _m_node_count(0), _m_key_compare(comp) {
    _initialize_header();
  }

  // TODO copy constructor
  _rb_tree(const _self& other)
      : _Base(other.get_node_allocator()), _m_node_count(0), _m_key_compare(other._m_key_compare) {
    if (other._root() == NULL) {
      _initialize_header();
    } else {
      _m_header._m_color = RED;
      _root() = _copy_tree(other._root(), _end());
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

  // 3. Iterators
  iterator begin(void) { return iterator(_m_header._m_left); }
  const_iterator begin(void) const { return const_iterator(_m_header._m_left); }
  // const_iterator begin(void) const { return const_cast<base_ptr>(&_m_header._m_left); }

  iterator end(void) { return iterator(&_m_header); }
  const_iterator end(void) const { return const_cast<base_ptr>(&_m_header); }

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

  /**
   * @brief single element version of insert
   *
   * @param val
   * @return ft::pair<iterator, bool>
   */
  ft::pair<iterator, bool> insert(const value_type& val) {
    link_type loc = _root();        // root
    link_type loc_parent = _end();  // header
    bool is_left = true;

    while (loc != NULL) {  // find location
      loc_parent = loc;
      is_left = _m_key_compare(KeyOfValue()(val), _get_key(loc));
      loc = is_left ? _left(loc) : _right(loc);
    }

    // std::cout << std::endl;
    // this->printBT();  // FIXME: test code

    iterator iter(loc_parent);
    if (is_left) {  // 마지막에 왼쪽으로 내려온 경우
      //  insert left
      if (iter == begin()) {  // if there are no root
        return ft::pair<iterator, bool>(_insert(loc, loc_parent, val), true);  // make root
      } else {
        --iter;
      }
    }
    // check duplicated key
    if (_m_key_compare(_get_key(iter._m_node), KeyOfValue()(val))) {
      return ft::pair<iterator, bool>(_insert(loc, loc_parent, val), true);
    }
    std::cout << " <- duplicated key!";
    return ft::pair<iterator, bool>(iter, false);
  }

  /**
   * @brief with hint version of insert
   * @note hint position 앞에 가장 가까운 곳에 위치하도록 insert
   *
   * @param position - hint position
   * @param val
   * @return iterator
   */
  iterator insert(iterator position, const value_type& val) {
    if (position == begin()) {
      // check valid hint
      if (position != end() &&  // size() > 0
          _m_key_compare(KeyOfValue()(val),
                         _get_key(position._m_node))) {  // val < *hint
        // TODO update minimum?
        return _insert(position._m_node, position._m_node, val);
      } else {  // invalid hint => single element function call
        return insert(val).first;
      }
    } else if (position == end()) {
      if (_m_key_compare(_get_key(_rightmost()), KeyOfValue()(val))) {  // rightmost < val
                                                                        // TODO update maximum?
        return _insert(NULL, _rightmost(), val);
      } else {
        // invlaid hint => single element function call
        return insert(val).first;
      }
    } else {
      iterator before = position;

      --before;
      if (_m_key_compare(_get_key(before._m_node), KeyOfValue()(val)) &&
          _m_key_compare(KeyOfValue()(val), _get_key(position._m_node))) {
        // *(hint - 1) < val < *hint
        if (before._m_node->_m_right == NULL) {
          return _insert(NULL, before._m_node, val);
        } else {                       // there are right subtree
          return insert(before, val);  // Recursive function call
          // return _insert(position._m_node, val);
        }
      } else {
        // invalid hint => single element function call
        return insert(val).first;
      }
    }
  }

  // insert - range
  template <typename InputIter>
  void insert(InputIter first, InputIter last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

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
  iterator find(const key_type& key) {
    iterator res = lower_bound(key);
    return (res == end() || _m_key_compare(key, KeyOfValue()(*res))) ? end() : res;
  }

  const_iterator find(const key_type& key) const {
    const_iterator res = lower_bound(key);
    return (res == end() || _m_key_compare(key, KeyOfValue()(*res))) ? end() : res;
  }

  /// equal_range
  // ft::pair<iterator, iterator> equal_range(const key_type& key);
  // ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

  /**
   * @return iterator - pointing to the first element that is not less than key (greater or equal)
   */
  iterator lower_bound(const key_type& key) {
    link_type current = _root();  // traversal
    link_type res = _end();       // result

    while (current != NULL) {
      if (!_m_key_compare(_get_key(current), key)) {  // !(current < key) == (current >= key)
        res = current;                                // update result
        current = _left(current);                     // go to left
      } else {                                        // current < key
        current = _right(current);                    // go to right
      }
    }
    return iterator(res);
  }

  const_iterator lower_bound(const key_type& key) const {
    link_type current = _root();
    link_type res = _end();

    while (current != NULL) {
      if (!_m_key_compare(_get_key(current), key)) {
        res = current;
        current = _left(current);
      } else {
        current = _right(current);
      }
    }
    return const_iterator(res);
  }

  /**
   * @return iterator - pointing to the first element whose key is considered to go after key
   */
  iterator upper_bound(const key_type& key) {
    link_type current = _root();  // traversal
    link_type res = _end();       // result

    while (current != NULL) {
      if (_m_key_compare(key, _get_key(current))) {  // current > key
        res = current;                               // update res
        current = _left(current);                    // go to left
      } else {                                       // current <= key
        current = _right(current);                   // go to right
      }
    }
    return iterator(res);
  }

  const_iterator upper_bound(const key_type& key) const {
    link_type current = _root();
    link_type res = _end();

    while (current != NULL) {
      if (_m_key_compare(key, _get_key(current))) {
        res = current;
        current = _left(current);
      } else {
        current = _right(current);
      }
    }
    return const_iterator(res);
  }

  // 7. Observers
  key_compare key_comp(void) const { return _m_key_compare; }

  // !SECTION

  // SECTION private functions (node)
 private:
  link_type _root(void) const { return static_cast<link_type>(_m_header._m_parent); }

  // get header
  link_type _end(void) {
    return static_cast<link_type>(&_m_header);
    // return static_cast<link_type>(end()._m_node);
  }

  value_type _get_value(link_type node) const { return node->_m_value_field; }
  value_type _get_value(base_ptr node) const {
    return static_cast<link_type>(node)->_m_value_field;
  }

  key_type _get_key(link_type node) const { return KeyOfValue()(_get_value(node)); }
  key_type _get_key(base_ptr node) const {
    return KeyOfValue()(_get_value(static_cast<link_type>(node)));
  }

  // & : for use lhs(assignable)
  link_type _left(base_ptr node) const { return static_cast<link_type>(node->_m_left); }

  link_type _right(base_ptr node) const { return static_cast<link_type>(node->_m_right); }

  link_type _parent(base_ptr node) const { return static_cast<link_type>(node->_m_parent); }

  link_type _leftmost(void) const { return static_cast<link_type>(_m_header._m_left); }

  link_type _rightmost(void) const { return static_cast<link_type>(_m_header._m_right); }

  link_type _create_node(const value_type& value) {
    link_type tmp = allocate_node();

    try {
      _m_alloc.construct(tmp, value);
    } catch (...) {
      _m_alloc.destroy(tmp);
      deallocate_node(tmp);
    }
    // _m_alloc.construct(tmp, value);
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

  void _initialize_header(void) {
    _m_header._m_color = RED;
    _m_header._m_parent = NULL;
    _m_header._m_left = &_m_header;
    _m_header._m_right = &_m_header;
  }

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
  iterator _insert(base_ptr _x, base_ptr _y, const value_type& val) {
    link_type x = static_cast<link_type>(_x);
    link_type y = static_cast<link_type>(_y);
    link_type new_node;

    new_node = _create_node(val);
    if (y == _end() || x != NULL || _m_key_compare(KeyOfValue()(val), _get_key(y))) {
      y->_m_left = new_node;

      if (y == _end()) {                 // there are no root
        _m_header._m_parent = new_node;  // make root
        _m_header._m_right = new_node;   // update rightmost
      } else if (y == _leftmost()) {     // update leftmost
        _m_header._m_left = new_node;
      }
    } else {
      y->_m_right = new_node;
      if (y == _rightmost()) {  // update rightmost
        _m_header._m_right = new_node;
      }
    }
    // set y of new_node
    new_node->_m_parent = y;
    _rebalance_for_insert(new_node, _m_header._m_parent);
    ++_m_node_count;

    return iterator(new_node);
  }

  // FIXME: test code BEGIN
  void printBT(const std::string& prefix, const link_type node, bool isLeft) {
    if (node != nullptr) {
      std::cout << prefix;

      std::cout << (isLeft ? "├──" : "└──");

      // print the value of the node
      std::cout << KeyOfValue()(node->_m_value_field) << std::endl;

      // enter the next tree level - left and right branch
      printBT(prefix + (isLeft ? "│   " : "    "), static_cast<link_type>(node->_m_left), true);
      printBT(prefix + (isLeft ? "│   " : "    "), static_cast<link_type>(node->_m_right), false);
    }
  }

  void printBT() { printBT("", static_cast<link_type>(this->_m_header._m_parent), false); }

  // FIXME : test code END

  // !SECTION
};
// !SECTION

// SECTION Non-member function
// CHECK check rotate functions
void _rotate_left(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
  _rb_tree_node_base* y = x->_m_right;
  x->_m_right = y->_m_left;
  if (y->_m_left != 0) y->_m_left->_m_parent = x;
  y->_m_parent = x->_m_parent;

  if (x == root)
    root = y;
  else if (x == x->_m_parent->_m_left)
    x->_m_parent->_m_left = y;
  else
    x->_m_parent->_m_right = y;
  y->_m_left = x;
  x->_m_parent = y;
}

void _rotate_right(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
  _rb_tree_node_base* y = x->_m_left;
  x->_m_left = y->_m_right;
  if (y->_m_right != 0) y->_m_right->_m_parent = x;
  y->_m_parent = x->_m_parent;

  if (x == root)
    root = y;
  else if (x == x->_m_parent->_m_right)
    x->_m_parent->_m_right = y;
  else
    x->_m_parent->_m_left = y;
  y->_m_right = x;
  x->_m_parent = y;
}

void _rebalance_for_insert(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
  bool is_parent_left_child;
  // x->_m_color = RED;
  while (x != root && x->_m_parent->_m_color == RED) {
    is_parent_left_child = (x->_m_parent == x->_m_parent->_m_parent->_m_left);
    _rb_tree_node_base* y =
        is_parent_left_child ? x->_m_parent->_m_parent->_m_right : x->_m_parent->_m_parent->_m_left;

    if (y && y->_m_color == RED) {  // 삼촌 노드가 RED일 경우 -> Recolorizing (CASE 1)
      x->_m_parent->_m_color = BLACK;
      y->_m_color = BLACK;
      x->_m_parent->_m_parent->_m_color = RED;
      x = x->_m_parent->_m_parent;
    } else if (is_parent_left_child) {    // 삼촌 노드가 BLACK일 경우 -> Restructuring
      if (x == x->_m_parent->_m_right) {  // CASE 2
        x = x->_m_parent;
        _rotate_left(x, root);
      }
      // CASE 3
      x->_m_parent->_m_color = BLACK;
      x->_m_parent->_m_parent->_m_color = RED;
      _rotate_right(x->_m_parent->_m_parent, root);
    } else if (!is_parent_left_child) {  // 삼촌 노드가 BLACK일 경우 -> Restructuring
      if (x == x->_m_parent->_m_left) {  // CASE 2
        x = x->_m_parent;
        _rotate_right(x, root);
      }
      // CASE 3
      x->_m_parent->_m_color = BLACK;
      x->_m_parent->_m_parent->_m_color = RED;
      _rotate_left(x->_m_parent->_m_parent, root);
    }
  }
  root->_m_color = BLACK;
}

void _rebalance_for_erase(_rb_tree_node_base* x, _rb_tree_node_base* root);

}  // namespace ft

#endif