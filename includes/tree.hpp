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
#include <iterator>    // std::bidirectional_iterator:tag
#include <memory>      // std::allocator<T>

#include "iterator.hpp"  // ft::reverse_iterator
#include "utility.hpp"   // ft::pair

namespace ft {
enum _rb_tree_color { RED = false, BLACK = true };

/** SECTION node_base
 * @brief pointer(parent, left, right), NO value
 */
struct _rb_tree_node_base {
  typedef _rb_tree_node_base* base_ptr;

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
struct _rb_tree_node : public _rb_tree_node_base {
  typedef Val value_type;
  typedef _rb_tree_node<value_type>* link_type;  // value access O
  // typedef _rb_tree_node_base::base_ptr base_ptr;  // value access X

  // member object
  value_type _m_value_field;  // Val == ft::pair<key_type, mapped_type> == {key, value}

  // constructor
  _rb_tree_node(const value_type& value) : _m_value_field(value) {}
};
// !SECTION node

// SECTION iterator
template <typename Val, typename Ref, typename Ptr>
struct _rb_tree_iterator {
  typedef Val value_type;
  typedef Ref reference;
  typedef Ptr pointer;

  typedef _rb_tree_node_base::base_ptr base_ptr;
  typedef _rb_tree_node<Val>* link_type;
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
  typedef Alloc allocator_type;
  typedef _rb_tree_node<value_type>* link_type;

  // member object
  allocator_type _m_node_allocator;
  _rb_tree_node_base _m_header;  // tree header

  // constructor
  _rb_tree_base(const allocator_type& alloc = allocator_type()) : _m_node_allocator(alloc) {}

  // get_allocator
  allocator_type get_allocator(void) const { return _m_node_allocator; }

  // allocate new node
  link_type get_node(void) { return _m_node_allocator.allocate(1); }

  // deallocate node
  void deallocate_node(_rb_tree_node<value_type>* p) { _m_node_allocator.deallocate(p, 1); }
};
// !SECTION

// SECTION rb_tree
/**
 * @brief  RB_Tree
 *
 * @tparam Key - key type
 * @tparam Val - ft::pair<key_type, mapped_type>
 * @tparam KeyOfValue
 * @tparam Compare - compare function
 * @tparam Alloc
 */
// TODO Add KeyOfValue template parameter when I needed
// template <typename Key, typename Val, typename KeyOfValue, typename Compare,
//           typename Alloc = std::allocator<Val> >
template <typename Key, typename Val, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Val> >
class _rb_tree : protected _rb_tree_base<Val, Alloc> {
  // tree_base
 private:
  typedef _rb_tree_base<Val, Alloc> _Base;
  typedef _rb_tree<Key, Val, Compare, Alloc> _self;

 public:
  typedef Key key_type;
  typedef Val value_type;
  typedef Compare key_compare;
  typedef typename _Base::allocator_type allocator_type;
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
  using _Base::_m_header;
  using _Base::_m_node_allocator;
  using _Base::deallocate_node;
  using _Base::get_node;

  size_type _m_node_count;
  key_compare _m_key_compare;

 public:
  // constructor
  _rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      : _Base(alloc), _m_node_count(0), _m_key_compare(comp) {
    _empty_initialize();
  }

  // copy constructor
  _rb_tree(const _self& other)
      : _Base(other.get_allocator()), _m_node_count(0), _m_key_compare(other._m_key_compare) {
    // if other is empty ??
    // empty_initialize()
    // else ???
    // color, root, left, right
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
      if (other.get_root() == NULL) {
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
  allocator_type get_allocator(void) const { return _Base::get_allocator(); }

  // 2. Element access
  value_type& at(const key_type key);
  const value_type& at(const key_type key) const;

  value_type& operator[](const key_type& key);

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
  bool empty(void) const { return _m_node_count == 0; }

  size_type size(void) const { return _m_node_count; }
  size_type max_size(void) const { return _m_node_allocator.max_size(); }

  // 5. Modifiers
  // clear
  void clear(void) {}

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

  // SECTION protected functions (node)
 protected:
  link_type& get_root(void) const { return static_cast<link_type>(_m_header._m_parent); }

  link_type& get_left(link_type& node) const { return static_cast<link_type>(node->_m_left); }

  link_type& get_right(link_type& node) const { return static_cast<link_type>(node->_m_right); }

  link_type& get_parent(link_type& node) const { return static_cast<link_type>(node->_m_parent); }

  link_type create_node(const value_type& value) {
    link_type tmp = get_node();

    _m_node_allocator.construct(tmp->_m_value_field, value);
    return tmp;
  }

  link_type clone_node(const link_type other) {
    link_type tmp = create_node(other->_m_value_field);

    tmp->_m_color = other->_m_color;
    tmp->_m_left = NULL;
    tmp->_m_right = NULL;

    return tmp;
  }
  // !SECTION

  void destroy_node(link_type p) {
    _m_node_allocator.destroy(p->_m_value_field);
    deallocate_node(p);
  }

  // SECTION private functions
 private:
  void _empty_initialize(void) {
    // _m_header initialization
    _m_header._m_color = RED;
    _m_header._m_parent = NULL;
    _m_header._m_left = NULL;
    _m_header._m_right = NULL;
  }
  // !SECTION
};
// !SECTION

}  // namespace ft

#endif