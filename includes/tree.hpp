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
#include <iterator>    // std::bidirectional_iterator_tag
#include <memory>      // std::allocator<T>

#include "algorithm.hpp"  // ft::_swap
#include "function.hpp"   // ft::select1st
#include "iterator.hpp"   // ft::reverse_iterator
#include "utility.hpp"    // ft::pair

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

  //	minimum & maximum
  static base_ptr _minimum(base_ptr node) {
    while (node->_m_left != NULL) {
      node = node->_m_left;
    }
    return node;
  }

  static base_ptr _maximum(base_ptr node) {
    while (node->_m_right != NULL) {
      node = node->_m_right;
    }
    return node;
  }
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

  typedef _rb_tree_iterator<Val, Val&, Val*> iterator;

  typedef ft::_rb_tree_node<Val>* link_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;

  typedef _rb_tree_iterator<Val, Ref, Ptr> _self;

  // member object
  _rb_tree_node_base* _m_node;  // iterator

  // Constructor
  _rb_tree_iterator(void) {}

  // node_base constructor
  _rb_tree_iterator(_rb_tree_node_base* node) : _m_node(node) {}
  // _rb_tree_iterator(const _rb_tree_node_base* node) : _m_node(node) {}

  // Copy Constructor
  _rb_tree_iterator(const iterator& iter) : _m_node(iter._m_node) {}

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
      _rb_tree_node_base* parent = _m_node->_m_parent;

      while (_m_node == parent->_m_right) {
        _m_node = parent;
        parent = parent->_m_parent;
      }
      // if (_m_node != root)
      // if (_m_node != _m_node->_m_parent) _m_node = parent;
      if (_m_node->_m_right != parent) _m_node = parent;
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
      _rb_tree_node_base* parent = _m_node->_m_parent;

      while (_m_node == parent->_m_left) {
        _m_node = parent;
        parent = parent->_m_parent;
      }
      _m_node = parent;
    }
  }
};
// SECTION Non-member function
// SECTION iterator non-member function
// (const_)iterator == (const_)iterator
template <typename Val, typename Ref, typename Ptr>
bool operator==(const _rb_tree_iterator<Val, Ref, Ptr>& lhs,
                const _rb_tree_iterator<Val, Ref, Ptr>& rhs) {
  return lhs._m_node == rhs._m_node;
}

// const_iterator == iterator
template <typename Val>
bool operator==(const _rb_tree_iterator<Val, const Val&, const Val*>& lhs,
                const _rb_tree_iterator<Val, Val&, Val*>& rhs) {
  return lhs._m_node == rhs._m_node;
};

// iterator == const_iterator
template <typename Val>
bool operator==(const _rb_tree_iterator<Val, Val&, Val*>& lhs,
                const _rb_tree_iterator<Val, const Val&, const Val*>& rhs) {
  return lhs._m_node == rhs._m_node;
};

// (const_)iterator != (const_)iterator
template <typename Val, typename Ref, typename Ptr>
bool operator!=(const _rb_tree_iterator<Val, Ref, Ptr>& lhs,
                const _rb_tree_iterator<Val, Ref, Ptr>& rhs) {
  return lhs._m_node != rhs._m_node;
};

// const_iterator != iterator
template <typename Val>
bool operator!=(const _rb_tree_iterator<Val, const Val&, const Val*>& lhs,
                const _rb_tree_iterator<Val, Val&, Val*>& rhs) {
  return lhs._m_node != rhs._m_node;
};

// iterator != const_iterator
template <typename Val>
bool operator!=(const _rb_tree_iterator<Val, Val&, Val*>& lhs,
                const _rb_tree_iterator<Val, const Val&, const Val*>& rhs) {
  return lhs._m_node != rhs._m_node;
};

// !SECTION iterator non-member function

// !SECTION
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
  typedef _rb_tree<Key, Val, KeyOfValue, Compare, Alloc> _self;

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

  // copy constructor
  _rb_tree(const _rb_tree& other)
      : _Base(other.get_node_allocator()), _m_node_count(0), _m_key_compare(other._m_key_compare) {
    if (other._root() == NULL) {
      _initialize_header();
    } else {
      // _m_header._m_color = RED;
      _m_header._m_parent = _copy_tree(other._root(), _end());
      _m_header._m_left = _minimum(_root());        // lefmost
      _m_header._m_right = _maximum(_root());       // rightmost
      _m_header._m_parent->_m_parent = &_m_header;  // CHECK header	 <- ??
    }
    _m_node_count = other._m_node_count;
  }

  // destructor
  ~_rb_tree(void) {}

  // operator=
  _rb_tree& operator=(const _rb_tree& other) {
    if (this != &other) {
      clear();
      _m_node_count = 0;
      _m_key_compare = other._m_key_compare;
      if (other._root() == NULL) {    // reset header
        _m_header._m_parent = NULL;   // root
        _m_header._m_left = _end();   // leftmost
        _m_header._m_right = _end();  // rightmost
      } else {
        _m_header._m_parent = _copy_tree(other._root(), _end());  // root
        _m_header._m_left = _minimum(_root());                    // leftmost
        _m_header._m_right = _maximum(_root());                   // rightmost
        _m_node_count = other._m_node_count;                      // node_count
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

  // iterator end(void) { return iterator(&_m_header); }
  iterator end(void) { return &_m_header; }
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
  void clear(void) {
    if (_m_node_count != 0) {
      _erase(_root());
      _m_header._m_left = &_m_header;
      _m_header._m_parent = NULL;
      _m_header._m_right = &_m_header;
      _m_node_count = 0;
    }
  }

  /**
   * @brief single element version of insert
   *
   * @param val
   * @return ft::pair<iterator, bool>
   */
  ft::pair<iterator, bool> insert_unique(const value_type& val) {
    link_type loc = _root();        // root
    link_type loc_parent = _end();  // header
    bool is_left = true;

    while (loc != NULL) {  // find location
      loc_parent = loc;
      is_left = _m_key_compare(KeyOfValue()(val), _get_key(loc));
      loc = is_left ? _left(loc) : _right(loc);
    }

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
  iterator insert_unique(iterator position, const value_type& val) {
    if (position == begin()) {
      // check valid hint
      if (position != end() &&  // size() > 0
          _m_key_compare(KeyOfValue()(val),
                         _get_key(position._m_node))) {  // val < *hint
        return _insert(position._m_node, position._m_node, val);
      } else {  // invalid hint => single element function call
        return insert_unique(val).first;
      }
    } else if (position == end()) {
      if (_m_key_compare(_get_key(_rightmost()), KeyOfValue()(val))) {  // rightmost < val
        return _insert(NULL, _rightmost(), val);
      } else {
        // invlaid hint => single element function call
        return insert_unique(val).first;
      }
    } else {
      iterator before = position;

      --before;
      if (_m_key_compare(_get_key(before._m_node), KeyOfValue()(val)) &&
          _m_key_compare(KeyOfValue()(val), _get_key(position._m_node))) {
        // *(hint - 1) < val < *hint
        if (before._m_node->_m_right == NULL) {
          return _insert(NULL, before._m_node, val);
        } else {  // there are right subtree
          // return insert_unique(before, val);  // Recursive function call
          return _insert(position._m_node, position._m_node, val);
        }
      } else {
        // invalid hint => single element function call
        return insert_unique(val).first;
      }
    }
  }

  // insert - range
  template <typename InputIter>
  void insert_unique(InputIter first, InputIter last) {
    for (; first != last; ++first) {
      insert_unique(*first);
    }
  }

  // erase
  void erase(iterator position) {
    link_type node = static_cast<link_type>(_rebalance_for_erase(
        position._m_node, _m_header._m_parent, _m_header._m_left, _m_header._m_right));
    // link_type node = (link_type)_rebalance_for_erase(position._m_node, _m_header._m_parent,
    //                                                  _m_header._m_left, _m_header._m_right);
    _destroy_node(node);
    --_m_node_count;
    // printBT();
  }

  size_type erase(const key_type& key) {
    ft::pair<iterator, iterator> __p = equal_range(key);
    size_type __n = std::distance(__p.first, __p.second);
    erase(__p.first, __p.second);
    return __n;
  }

  // [first, last)
  void erase(iterator first, iterator last) {
    if (first == begin() && last == end()) {
      clear();
    } else {
      while (first != last) {
        iterator tmp(first++);
        erase(tmp);
      }
    }
  }

  // swap
  void swap(_self& other) {
    if (_root() == NULL) {
      if (other._root() != NULL) {
        *this = other;  // assign operator=

        // reset other tree
        other._m_header._m_parent = NULL;         // root
        other._m_header._m_left = other._end();   // leftmost
        other._m_header._m_right = other._end();  // rightmost
      }
    } else if (other._root() == NULL) {
      other = *this;  // assign operator=

      // reset this tree
      _m_header._m_parent = NULL;   // root
      _m_header._m_left = _end();   // leftmost
      _m_header._m_right = _end();  // rightmost

    } else {
      ft::_swap(_m_header._m_parent, other._m_header._m_parent);
      ft::_swap(_m_header._m_left, other._m_header._m_left);
      ft::_swap(_m_header._m_right, other._m_header._m_right);

      _root()->_m_parent = _end();
      other._root()->_m_parent = other._end();
    }
    ft::_swap(this->_m_node_count, other._m_node_count);
    ft::_swap(this->_m_key_compare, other._m_key_compare);
  }

  // 6. Lookup
  // count
  size_type count(const key_type& key) const {
    pair<const_iterator, const_iterator> p = equal_range(key);
    size_type n = std::distance(p.first, p.second);
    return n;
  }

  // find
  iterator find(const key_type& key) {
    iterator res = lower_bound(key);
    return (res == end() || _m_key_compare(key, KeyOfValue()(*res))) ? end() : res;
  }

  const_iterator find(const key_type& key) const {
    const_iterator res = lower_bound(key);
    return (res == end() || _m_key_compare(key, KeyOfValue()(*res))) ? end() : res;
  }

  // equal_range
  ft::pair<iterator, iterator> equal_range(const key_type& key) {
    return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
    return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
  }

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

  link_type _leftmost(void) const { return static_cast<link_type>(_m_header._m_left); }

  link_type _rightmost(void) const { return static_cast<link_type>(_m_header._m_right); }

  link_type _end(void) const { return static_cast<link_type>(const_cast<base_ptr>((&_m_header))); }

  value_type _get_value(link_type node) const { return node->_m_value_field; }
  value_type _get_value(base_ptr node) const {
    return static_cast<link_type>(node)->_m_value_field;
  }

  key_type _get_key(link_type node) const { return KeyOfValue()(_get_value(node)); }
  key_type _get_key(base_ptr node) const {
    return KeyOfValue()(_get_value(static_cast<link_type>(node)));
  }

  link_type _left(base_ptr node) const { return static_cast<link_type>(node->_m_left); }

  link_type _right(base_ptr node) const { return static_cast<link_type>(node->_m_right); }

  link_type _parent(base_ptr node) const { return static_cast<link_type>(node->_m_parent); }

  link_type _minimum(link_type node) const {
    return static_cast<link_type>(_rb_tree_node_base::_minimum(node));
  }

  link_type _maximum(link_type node) const {
    return static_cast<link_type>(_rb_tree_node_base::_maximum(node));
  }

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
    // _m_alloc.destroy(p->_m_value_field);
    _m_alloc.destroy(p);
    deallocate_node(p);
  }

  void _initialize_header(void) {
    _m_header._m_color = RED;
    _m_header._m_parent = NULL;
    _m_header._m_left = &_m_header;
    _m_header._m_right = &_m_header;
  }

  /**
   * @brief tree 복사
   *
   * @param src_current - 복사될 노드
   * @param dst_parent - 복사할 위치의 부모 노드
   *
   * @return dst_current - 복사해서 새롭게 생성한 노드
   *
   * src_current의 right 노드가 없을 때까지(rightmost까지) 재귀호출
   */
  link_type _copy_tree(link_type src_current, link_type dst_parent) {
    link_type dst_current = _clone_node(src_current);  // clone new node

    dst_current->_m_parent = dst_parent;  // 자식에서 부모 연결

    if (src_current->_m_right) {  // 오른쪽 서브트리 있으면 -> recursive call
      dst_current->_m_right = _copy_tree(_right(src_current), dst_current);
    }
    // 오른쪽 서브트리 없을 경우
    dst_parent = dst_current;          // 부모에서 오른쪽 자식 연결
    src_current = _left(src_current);  // 왼쪽 노드 탐색 시작
    while (src_current != NULL) {      // 왼쪽 서브트리 탐색
      link_type y = _clone_node(src_current);
      dst_parent->_m_left = y;      // 부모에서 왼쪽 자식 연결
      y->_m_parent = dst_parent;    // 자식에서 부모 연결
      if (src_current->_m_right) {  // 다시 오른쪽 서브트리 확인
        y->_m_right = _copy_tree(_right(src_current), y);
      }
      dst_parent = y;
      src_current = _left(src_current);
    }

    return dst_current;
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

  /**
   * @brief erase without rebalancing for clear()
   */
  void _erase(link_type x) {
    while (x != NULL) {
      _erase(_right(x));
      link_type y = _left(x);
      _destroy_node(x);
      x = y;
    }
  }

  // for test code BEGIN
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

  // !SECTION
};
// !SECTION

// SECTION Non-member function

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

/**
 * @brief erase with rebalance
 *
 * @param __z - 삭제하려는 노드
 * @param __root - root node
 * @param __leftmost - tree에서 최소값 (header의 left)
 * @param __rightmost - tree에서 최대값 (header의 right)
 * @return _rb_tree_node_base* - 삭제하려는 노드
 */
_rb_tree_node_base* _rebalance_for_erase(_rb_tree_node_base* __z, _rb_tree_node_base*& __root,
                                         _rb_tree_node_base*& __leftmost,
                                         _rb_tree_node_base*& __rightmost) {
  _rb_tree_node_base* __y = __z;  // 실제 삭제하려는 successor node (return)
  _rb_tree_node_base* __x = NULL;
  _rb_tree_node_base* __x_parent = NULL;

  if (__y->_m_left == NULL) {
    __x = __y->_m_right;

  } else if (__y->_m_right == NULL) {
    __x = __y->_m_left;

  } else {  // 자식이 2명인 경우 -> successor
    __y = __y->_m_right;
    while (__y->_m_left != NULL) __y = __y->_m_left;
    __x = __y->_m_right;  // x = successor's right child node
  }

  if (__y != __z) {  // successor 선택한 경우
    __z->_m_left->_m_parent = __y;
    __y->_m_left = __z->_m_left;
    if (__y != __z->_m_right) {
      __x_parent = __y->_m_parent;
      if (__x) __x->_m_parent = __y->_m_parent;
      __y->_m_parent->_m_left = __x;  // __y must be a child of _m_left
      __y->_m_right = __z->_m_right;
      __z->_m_right->_m_parent = __y;
    } else {
      __x_parent = __y;
    }

    // 형제 노드?
    if (__root == __z) {                          // 삭제하려는 노드가 root인 경우
      __root = __y;                               // root에 successor 대입
    } else if (__z->_m_parent->_m_left == __z) {  // 노드가 부모의 왼쪽 자식일 때
      __z->_m_parent->_m_left = __y;
    } else {  // 오른쪽 자식일 때
      __z->_m_parent->_m_right = __y;
    }

    __y->_m_parent = __z->_m_parent;
    // ft::_swap(__y->_m_color, __z->_m_color);
    ft::_swap(__y->_m_color, __z->_m_color);
    __y = __z;
    // __y now points to node to be actually deleted
  } else {  // y가 처음 삭제하려는 노드 그대로인 경우
    __x_parent = __y->_m_parent;
    if (__x) __x->_m_parent = __y->_m_parent;
    if (__root == __z)
      __root = __x;
    else if (__z->_m_parent->_m_left == __z)
      __z->_m_parent->_m_left = __x;
    else
      __z->_m_parent->_m_right = __x;
    if (__leftmost == __z) {
      if (__z->_m_right == 0) {  // __z->_m_left must be null also
        __leftmost = __z->_m_parent;
      }
      // makes __leftmost == _M_header if __z == __root
      else {
        __leftmost = _rb_tree_node_base::_minimum(__x);
      }
    }
    if (__rightmost == __z) {
      if (__z->_m_left == 0) {  // __z->_m_right must be null also
        __rightmost = __z->_m_parent;
      } else {  // __x == __z->_m_left
                // makes __rightmost == _M_header if __z == __root
        __rightmost = _rb_tree_node_base::_maximum(__x);
      }
    }
  }

  // BLACK이면 속성 위반 -> extra black 부여 -> doubly black 해결해야 함
  if (__y->_m_color != RED) {  // 삭제하려는 노드가 BLACK인 경우 ->
    while (__x != __root && (__x == 0 || __x->_m_color == BLACK)) {
      if (__x == __x_parent->_m_left) {
        _rb_tree_node_base* __w = __x_parent->_m_right;
        if (__w->_m_color == RED) {
          __w->_m_color = BLACK;
          __x_parent->_m_color = RED;
          _rotate_left(__x_parent, __root);
          __w = __x_parent->_m_right;
        }
        if ((__w->_m_left == 0 || __w->_m_left->_m_color == BLACK) &&
            (__w->_m_right == 0 || __w->_m_right->_m_color == BLACK)) {
          __w->_m_color = RED;
          __x = __x_parent;
          __x_parent = __x_parent->_m_parent;
        } else {
          if (__w->_m_right == 0 || __w->_m_right->_m_color == BLACK) {
            __w->_m_left->_m_color = BLACK;
            __w->_m_color = RED;
            _rotate_right(__w, __root);
            __w = __x_parent->_m_right;
          }
          __w->_m_color = __x_parent->_m_color;
          __x_parent->_m_color = BLACK;
          if (__w->_m_right) __w->_m_right->_m_color = BLACK;
          _rotate_left(__x_parent, __root);
          break;
        }
      } else {
        // same as above, with _m_right <-> _m_left.
        _rb_tree_node_base* __w = __x_parent->_m_left;
        if (__w->_m_color == RED) {
          __w->_m_color = BLACK;
          __x_parent->_m_color = RED;
          _rotate_right(__x_parent, __root);
          __w = __x_parent->_m_left;
        }
        if ((__w->_m_right == 0 || __w->_m_right->_m_color == BLACK) &&
            (__w->_m_left == 0 || __w->_m_left->_m_color == BLACK)) {
          __w->_m_color = RED;
          __x = __x_parent;
          __x_parent = __x_parent->_m_parent;
        } else {
          if (__w->_m_left == 0 || __w->_m_left->_m_color == BLACK) {
            __w->_m_right->_m_color = BLACK;
            __w->_m_color = RED;
            _rotate_left(__w, __root);
            __w = __x_parent->_m_left;
          }
          __w->_m_color = __x_parent->_m_color;
          __x_parent->_m_color = BLACK;
          if (__w->_m_left) __w->_m_left->_m_color = BLACK;
          _rotate_right(__x_parent, __root);
          break;
        }
      }
    }
    if (__x) __x->_m_color = BLACK;
  }
  return __y;
}

// SECTION rb_tree non-member function
// ==
template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
bool operator==(const _rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& lhs,
                const _rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& rhs) {
  return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
}

// <
template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc>
bool operator<(const _rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& lhs,
               const _rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& rhs) {
  return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

// !SECTION rb_tree non-member function

}  // namespace ft

#endif