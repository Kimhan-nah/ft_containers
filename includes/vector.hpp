/**
 * @file vector.hpp
 * @author hannkim (hannkim@student.42seoul.kr)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "vector_iterator.hpp"

namespace ft {

/** SECTION 1. vector_base
 * @brief RAII pattern for resource management
 *
 */
template <typename T, typename Allocator = std::allocator<T> >
class vector_base {
 protected:
  // member types
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

 protected:
  // member objects
  allocator_type _m_alloc;
  pointer _m_begin;    // _m_start (gcc), _begin(llvm)
  pointer _m_end;      // _m_finish
  pointer _m_end_cap;  // _m_end_of_storage

 protected:
  // vector_base constructors
  explicit vector_base(const allocator_type& alloc)
      : _m_alloc(alloc), _m_begin(NULL), _m_end(NULL), _m_end_cap(NULL) {}
  explicit vector_base(size_type count, const allocator_type& alloc)
      : _m_alloc(alloc),
        _m_begin(_m_alloc.allocate(count)),  // allocate & return pointer
        _m_end(_m_begin),
        _m_end_cap(_m_begin + count) {}
  ~vector_base(void) { _m_alloc.deallocate(_m_begin, _m_end_cap - _m_begin); }
};
// !SECTION 1

/** SECTION 2. vector
 * @brief Random-access iterator
 *
 * @tparam T - Type of the elements.
 * @tparam Allocator - Type of the allocator object used to define the storage
 * allocation model
 */
template <typename T, typename Allocator = std::allocator<T> >
class vector : protected vector_base<T, Allocator> {
 private:
  typedef vector_base<T, Allocator> _Base;

  // SECTION 2-1. Member types
 public:
  typedef T value_type;
  // typedef Allocator allocator_type;
  typedef typename _Base::allocator_type allocator_type;
  typedef typename _Base::reference reference;
  typedef typename _Base::const_reference const_reference;
  typedef typename _Base::pointer pointer;
  typedef typename _Base::const_pointer const_pointer;
  typedef typename _Base::size_type size_type;
  typedef typename _Base::difference_type difference_type;
  // vector_iterator == pointer == T*
  typedef ft::vector_iterator<pointer> iterator;
  typedef ft::vector_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  using _Base::_m_alloc;
  using _Base::_m_begin;
  using _Base::_m_end;
  using _Base::_m_end_cap;

  // !SECTION 2-1

  // SECTION 2-2. Member Functions
 public:
  // SECTION 2-2-1. constructors
  // 1. default
  explicit vector(const allocator_type& alloc = allocator_type()) : _Base(alloc) {}
  // 2. fill
  explicit vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _Base(count, alloc) {
    std::uninitialized_fill_n(_m_begin, count, value);
    _m_end = _m_end + count;
  }
  // 3-1. range - Input Iterator version
  template <typename InputIter>
  vector(typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type first,
         InputIter last, const allocator_type& alloc = allocator_type())
      : _Base(alloc) {
    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  // 3-2. range - Forward Iterator version
  // template <typename InputIter>
  // vector(typename ft::enable_if<is_forward_iterator>::type first, InputIter last,
  //        const allocator_type& alloc = allocator_type())
  //     : _Base(std::distance(first, last), alloc) {
  //   _m_end = std::uninitialized_copy(first, last, _m_begin);
  // }

  // 4. copy
  vector(const vector& other) : _Base(other.size(), other._m_alloc) {
    _m_end = std::uninitialized_copy(other._m_begin, other._m_end, _m_begin);
  }

  ~vector(void) {
    for (pointer p = _m_begin; p < _m_end; p++) {
      _m_alloc.destroy(p);
    }
  }

  vector& operator=(const vector& other) {
    assign(other.begin(), other.end());

    return *this;
  }

  // assign() : fill version
  void assign(size_type n, const value_type& value) {
    clear();
    for (size_type i = 0; i < n; i++) push_back(value);  // included reallocate
  }

  // assign() : range version
  template <typename InputIter>
  void assign(typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type first,
              InputIter last) {
    clear();
    for (; first != last; first++) push_back(*first);  // included reallocate
  }

  allocator_type get_allocator() const { return _m_alloc; }

  // !SECTION 2-2-1

  // SECTION 2-2-2. Element access
  // NOTE at, operator[], front, back, data

  /**
   * @brief access specified element with bounds checking
   * @exception bound-checked -> std::out_of_range
   * @note at != operator[]
   */
  reference at(size_type pos) {
    if (pos < size()) {
      return (*this)[pos];
    } else {  // exception
      throw std::out_of_range("ft::vector");
    }
  }

  const_reference at(size_type pos) const {
    if (pos < size()) {
      return (*this)[pos];
    } else {  // exception
      throw std::out_of_range("ft::vector");
    }
  }

  /**
   * @brief access specified element
   * @exception NO
   * @note bound-checked -> undefined behavior
   */
  reference operator[](size_type pos) { return *(_m_begin + pos); }
  const_reference operator[](size_type pos) const { return *(_m_begin + pos); }

  /**
   * @brief access the first element
   * @exception NO
   * @note empty container -> undefined behavior
   */
  reference front(void) { return *_m_begin; }
  const_reference front(void) const { return *_m_begin; }

  /**
   * @brief access the last element
   * @exception NO
   * @note empty container -> undefined behavior
   */
  reference back(void) { return *(_m_end - 1); }
  const_reference back(void) const { return *(_m_end - 1); }

  /**
   * @brief direct access to the underlying array
   * CHECK c++11 ?? (cplusplus)
   */
  // pointer data(void); ??
  value_type* data(void) { return _m_begin; }
  const value_type* data(void) const { return _m_begin; }

  // !SECTION 2-2-2

  // SECTION 2-2-3. Iterastors
  iterator begin(void) { return iterator(_m_begin); }
  const_iterator begin(void) const { return const_iterator(_m_begin); }

  iterator end(void) { return iterator(_m_end); }
  const_iterator end(void) const { return const_iterator(_m_end); }

  reverse_iterator rbegin(void) { return reverse_iterator(end()); }
  const_reverse_iterator rbegin(void) const {
    return const_reverse_iterator(end());
    // TODO
    // return const_reverse_iterator(_m_end);
  }

  reverse_iterator rend(void) { return reverse_iterator(begin()); }
  const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }

  // !SECTION 2-2-3

  // SECTION 2-2-4. Capacity
  // NOTE empty, size, max_size, reserve, capacity
  /**
   * @brief checks whether the container is empty
   * @exception No-Throw guarantee
   */
  bool empty(void) const { return _m_begin == _m_end; }

  /**
   * @brief returns the number of elements
   * @exception No-Throw guarantee
   */
  size_type size(void) const { return _m_end - _m_begin; }

  /**
   * @brief returns the maximum possible number of elements
   * @exception No-Throw guarantee
   */
  size_type max_size(void) const {
    return _m_alloc.max_size();
    // return size_type(-1) / sizeof(value_type); }
  }

  /**
   * @brief reserves storage
   * @exception STRONG
   * @exception BASIC
   */
  void reserve(size_type new_cap) {
    if (new_cap > capacity()) {  // reallocate -> STRONG
      vector tmp;

      tmp._m_begin = _m_alloc.allocate(new_cap);
      tmp._m_end = std::uninitialized_copy(_m_begin, _m_end, tmp._m_begin);
      tmp._m_end_cap = tmp._m_begin + new_cap;
      swap(tmp);
    }
    // otherwise, do nothing
  }

  size_type capacity(void) const { return _m_end_cap - _m_begin; }

  // !SECTION 2-2-4

  // SECTION 2-2-5. Modifiers
  // NOTE clear, insert, erase, push_back, pop_back, resize, swap

  /**
   * @brief clears the contents
   * @note erases all elements from the container
   */
  void clear(void) {
    erase(begin(), end());
    _m_end = _m_begin;
  }

  /**
   * @brief inserts elements
   */
  // 1. single element
  iterator insert(iterator pos, const value_type& val) {
    difference_type index = pos - begin();
    pointer p = _m_begin + index;

    if (size() + 1 > capacity()) {  // _m_end == _m_end_cap
      // reallocate
      vector tmp;

      size_type new_size = _get_new_capacity(size() + 1);
      tmp._m_begin = _m_alloc.allocate(new_size);
      tmp._m_end_cap = tmp._m_begin + new_size;
      tmp._m_end = std::uninitialized_copy(_m_begin, p, tmp._m_begin);  // [_m_begin, p)
      std::uninitialized_fill_n(tmp._m_end, 1, val);                    // insert single element
      ++tmp._m_end;
      tmp._m_end = std::uninitialized_copy(p, _m_end,
                                           tmp._m_end);  // [p, _m_end)
      swap(tmp);
    } else if (p == _m_end) {
      _construct_at_end(1, val);
    } else {
      pointer old_end = _m_end;

      _construct_at_end(1, val);
      std::copy_backward(p, old_end, _m_end);
      std::fill_n(p, 1, val);
    }
    return iterator(_m_begin + index);
  }

  // 2. fill
  void insert(iterator pos, size_type n, const value_type& val) {
    difference_type index = pos - begin();
    pointer p = _m_begin + index;

    if (n == 0) return;

    if (size() + n > capacity()) {
      // reallocate
      size_type new_size = _get_new_capacity(size() + n);
      vector tmp;

      tmp._m_begin = _m_alloc.allocate(new_size);
      tmp._m_end_cap = tmp._m_begin + new_size;
      tmp._m_end = std::uninitialized_copy(_m_begin, p, tmp._m_begin);  // [_m_begin, p)
      tmp._m_end = std::uninitialized_fill_n(tmp._m_end, n, val);       // insert elements
      tmp._m_end = std::uninitialized_copy(p, _m_end,
                                           tmp._m_end);  // [p, _m_end)
      swap(tmp);
    } else {
      pointer old_end = _m_end;

      _construct_at_end(n, val);
      std::copy_backward(p, old_end, _m_end);
      std::fill_n(p, n, val);
    }
  }

  //  3-1. range - Input Iterator version (using push_back or another insert version)
  template <typename InputIter>
  void insert(iterator pos,
              typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type first,
              InputIter last) {
    difference_type index = pos - begin();

    if (first == last) return;
    for (; first != last; first++) {
      insert(_m_begin + index, *first);  // possible to reallocate
      ++index;
    }
  }

  // 3-2. range - Forward Iterator version
  // template <typename InputIter>
  // void insert(iterator pos, typename ft::enable_if<!ft::is_integral<InputIter>::value,
  // InputIter>::type first,
  //                 InputIter last) {
  //   difference_type n = std::distance(first, last);
  //   pointer p = _m_begin + (pos - begin());

  //   if (size() + n > capacity()) {
  //     size_type new_size = _get_new_capacity(size() + n);
  //     vector tmp;

  //     tmp._m_begin = _m_alloc.allocate(new_size);
  //     tmp._m_end_cap = tmp._m_begin + new_size;
  //     tmp._m_end = std::uninitialized_copy(_m_begin, p, tmp._m_begin);  // [_m_begin, p)
  //     tmp._m_end = std::uninitialized_copy(first, last, tmp._m_end);
  //     tmp._m_end = std::uninitialized_copy(p, _m_end,
  //                                          tmp._m_end);  // [p, _m_end)
  //     swap(tmp);
  //   } else {
  //     pointer old_end = _m_end;

  //     _construct_at_end(n, *(_m_end - 1));
  //     std::copy_backward(p, old_end, _m_end);
  //     std::copy(first, last, p);
  //   }
  //   return iterator(_m_begin + dist);
  // }

  /**
   * @brief erases elements
   * @return typedef ft::vector_iterator<pointer> iterator
   *
   * @param pos - iterator
   * *pos - return *current (value current[0])
   * pos.base() - iterator_type current (vector_iterator)
   *
   * _m_end - pointer
   * end(void); function - return iterator(_m_end)
   *
   */
  iterator erase(iterator pos) {
    pointer _p = _m_begin + (pos - begin());

    if (_p != _m_end) {
      _m_alloc.destroy(_p);
      // relocate
      std::copy(pos + 1, end(), pos);
      --_m_end;
    }
    return iterator(_p);
  }

  // [first, last)
  iterator erase(iterator first, iterator last) {
    difference_type n = last - first;
    pointer _first = _m_begin + (first - begin());
    pointer _last = _m_begin + (last - begin());
    // pointer _p = _first;

    if (first != last) {
      for (pointer _p = _first; _p < _last; _p++) {
        _m_alloc.destroy(_p);
      }
      // relocate
      std::copy(last, end(), first);
      _m_end -= n;
    }
    return iterator(_first);
  }

  /**
   * @brief adds an element to the end
   */
  void push_back(const value_type& value) {
    if (size() + 1 > capacity()) {
      if (capacity() > 0)
        reserve(capacity() * 2);
      else
        reserve(2);
    }
    // construct at end
    _m_alloc.construct(_m_end, value);
    ++_m_end;
  }

  /**
   * @brief removes the last element
   */
  void pop_back(void) {
    erase(_m_end);
    --_m_end;
  }

  /*
   * @brief changes the number of elements stored
   */
  void resize(size_type new_size, value_type value = value_type()) {
    if (new_size < size()) {
      erase(_m_begin + new_size, _m_end);
      // _m_end = _m_begin + new_size;
    } else {
      insert(_m_end, new_size - size(), value);  // included reallocate
    }
  }

  /**
   * @brief swaps the contents
   */
  void swap(vector& other) {
    ft::_swap(_m_begin, other._m_begin);
    ft::_swap(_m_end, other._m_end);
    ft::_swap(_m_end_cap, other._m_end_cap);
  }

  // !SECTION 2-2-5
  // !SECTION 2-2

  // SECTION 2-3. Private Member Functions
 private:
  void _construct_at_end(size_type n, const value_type& val) {
    for (size_type i = 0; i < n; ++i) {
      _m_alloc.construct(_m_end, val);  // ERROR
      ++_m_end;
    }
  }

  // TODO refactoring
  size_type _get_new_capacity(size_type new_size) {
    size_type new_cap = _m_alloc.max_size() > capacity() * 2 ? capacity() * 2 : _m_alloc.max_size();

    return (new_size < new_cap ? new_cap : new_size);
  }
};
// !SECTION 2

// SECTION 3. Non-member functions
/** SECTION 3-1. Relational operators
 * @brief Compares the contents of two vectors
 */
template <typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs > rhs);
}

template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  // return rhs < lhs;
  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

// !SECTION 3-1

// SECTION 3-2. swap function
template <typename T, typename Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}
// !SECTION 3-2
// !SECTION 3
}  // namespace ft

#endif  // VECTOR_HPP