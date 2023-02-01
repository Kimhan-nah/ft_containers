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

// std::allocator<T>
#include <memory>
#include <vector>

// ft::reverse_iterator
#include "algorithm.hpp"
#include "iterator.hpp"
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
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::size_t size_t;
  typedef typename allocator_type::difference_type difference_type;

 protected:
  // member objects
  allocator_type _alloc;
  pointer _begin;    // _m_start (gcc), _begin(llvm)
  pointer _end;      // _m_finish
  pointer _end_cap;  // _m_end_of_storage

 protected:
  // vector_base constructors
  explicit vector_base(const allocator_type& alloc)
      : _alloc(alloc), _begin(NULL), _end(NULL), _end_cap(NULL) {}
  explicit vector_base(size_type count, const allocator_type& alloc)
      : _alloc(alloc),
        _begin(_alloc.allocator(count)),  // allocate & return pointer
        _end(_begin),
        _end_cap(_begin + count) {}
  ~vector_base(void) { _alloc.deallocate(_begin, _end_cap - _begin); }
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
class vector : public vector_base<T, Allocator> {
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

  // 이거 없으면  this->_alloc 해야됨 ㅎㅎ
  typedef typename _Base::_alloc _alloc;
  typedef typename _Base::_end _end;
  typedef typename _Base::_end_cap _end_cap;

  // TODO using test
  // using _Base::_alloc;
  // using _Base::_end;
  // using _Base::_end_cap;

  // vector_iterator == pointer == T*
  typedef ft::vector_iterator<pointer> iterator;
  typedef ft::vector_iterator<const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // !SECTION 2-1

  // SECTION 2-2. Member Functions
 public:
  // SECTION 2-2-1. constructors
  // 1. default
  explicit vector(const allocator_type& alloc = allocator_type())
      : _Base(alloc) {}
  // 2. fill
  explicit vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _Base(count, alloc) {
    std::uninitialized_fill_n(_begin, count, value);
    _end = _end + count;
  }
  // 3. range
  template <typename InputIt>
  vector(InputIt first, InputIt last,
         const allocator_type& alloc = allocator_type())
      : _Base(alloc) {
    _end = std::uninitialized_copy(first, last, _begin);
  }
  // 4. copy
  vector(const vector& other) : _Base(other._alloc, other.size()) {
    _end = std::uninitialized_copy(other._begin, other._end, _begin);
  }

  ~vector(void) {
    for (pointer p = _begin; p < _end; p++) {
      _alloc.destroy(p);
    }
  }

  vector& operator=(const vector& other) {
    assign(other.begin(), other.end());

    return *this;
  }

  // assign() : fill version
  // TODO Add enable_if???
  void assign(size_type n, const value_type& value) {
    clear();
    for (size_type i = 0; i < n; i++) push_back(value);  // included reallocate
  }

  // assign() : range version
  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    size_type n = last - first;

    clear();
    for (; first != last; first++) push_back(*first);  // included reallocate
  }

  allocator_type get_allocator() const { return _alloc; }

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
  reference operator[](size_type pos) { return *(_begin + pos); }
  const_reference operator[](size_type pos) const { return *(_begin + pos); }

  /**
   * @brief access the first element
   * @exception NO
   * @note empty container -> undefined behavior
   */
  reference front(void) { return *_begin; }
  const_reference front(void) const { return *_begin; }

  /**
   * @brief access the last element
   * @exception NO
   * @note empty container -> undefined behavior
   */
  reference back(void) { return *(_end - 1); }
  const_reference back(void) const { return *(_end - 1); }

  /**
   * @brief direct access to the underlying array
   * CHECK c++11 ?? (cplusplus)
   */
  // pointer data(void); ??
  value_type* data(void) { return _begin; }
  const value_type* data(void) const { return _begin; }

  // !SECTION 2-2-2

  // SECTION 2-2-3. Iterastors
  iterator begin(void) { return iterator(_begin); }
  const_iterator begin(void) const { return const_iterator(_begin); }

  iterator end(void) { return iterator(_end); }
  const_iterator end(void) const { return const_iterator(_end); }

  reverse_iterator rbegin(void) { return reverse_iterator(end()); }
  const_reverse_iterator rbegin(void) const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend(void) { return reverse_iterator(begin()); }
  const_reverse_iterator rend(void) const {
    return const_reverse_iterator(begin());
  }

  // !SECTION 2-2-3

  // SECTION 2-2-4. Capacity
  // NOTE empty, size, max_size, reserve, capacity
  /**
   * @brief checks whether the container is empty
   * @exception No-Throw guarantee
   */
  bool empty(void) const { return _begin == _end; }

  /**
   * @brief returns the number of elements
   * @exception No-Throw guarantee
   */
  size_type size(void) const { return _end - _begin; }

  /**
   * @brief returns the maximum possible number of elements
   * @exception No-Throw guarantee
   */
  size_type max_size(void) const {
    return _alloc.max_size();
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

      tmp._begin = _alloc.allocate(new_cap);
      tmp._end = std::uninitialized_copy(begin(), end(), tmp.begin());
      tmp._end_cap = tmp._begin + new_cap;
      swap(tmp);
    }
    // otherwise, do nothing
  }

  size_type capacity(void) const { return _end_cap - _begin; }

  // !SECTION 2-2-4

  // SECTION 2-2-5. Modifiers
  // NOTE clear, insert, erase, push_back, pop_back, resize, swap

  /**
   * @brief clears the contents
   * @note erases all elements from the container
   */
  void clear(void) { _end = erase(begin(), end()); }

  /**
   * @brief inserts elements
   */
  // 1. single element
  iterator insert(const_iterator pos, const value_type& val) {
    pointer p = _begin + (pos - begin());

    if (size() + 1 > capacity()) {  // _end == _end_cap
      // reallocate
      vector tmp;

      tmp._begin = _alloc.allocate(capacity() * 2);
      tmp._end = std::uninitialized_copy(_begin, p, tmp._begin);  // [_begin, p)
      // _alloc.construct(tmp._end, val);
      tmp._end = std::uninitialized_copy(p + 1, _end,
                                         tmp._end + 1);  // [p + 1, _end)
      swap(tmp);
    } else {
      // construct at end
      std::uninitialized_copy(_end - 1, _end, _end);

      // relocate
      std::copy_backward(p, _end - 1, _end - 1);

      // insert
      *p = val;

      // update _end
      ++_end;

      return iterator(p);
    }
  }

  // 2. fill
  iterator insert(const_iterator pos, size_type n, const value_type& val) {
    pointer p = _begin + (pos - begin());

    if (size() + n > capacity()) {
      // reallocate
      size_type new_size =
          (size() + n > capacity() * 2) ? size() + n : capacity() * 2;
      vector tmp;

      tmp._begin = _alloc.allocate(new_size);
      tmp._end = std::uninitialized_copy(_begin, p, tmp._begin);  // [_begin, p)
      tmp._end = std::uninitialized_copy(p + n, _end,
                                         tmp._end + n);  // [p + n, _end)
      swap(tmp);

    } else {
      // constructs at end
      std::uninitialized_copy(_end - n, _end, _end);

      // relocate [p, _end - n)
      std::copy_backward(p, _end - n, _end - 1);

      // insert
      std::fill_n(p, n, val);

      // update _end
      _end += n;
    }
    return iterator(p);
  }

  // 3. range
  template <typename InputIter>
  interator insert(const_iterator pos, InputIter first, InputIter last) {
    pointer p = _begin + (pos - begin());
    difference_type n = last - first;

    if (size() + n > capacity()) {
      // reallocate
      // CHECK Consider the new_size
      size_type new_size =
          (size() + n > capacity() * 2) ? size() + n : capacity() * 2;
      vector tmp;

      tmp._begin = _alloc.allocate(new_size);
      tmp._end = std::uninitialized_copy(_begin, p, tmp._begin);  // [_begin, p)

      // copy [first, last)
      tmp._end = std::uninitialized_copy(first, last, tmp._end);  // [p, p + n)

      tmp._end = std::uninitialized_copy(p + n, _end,
                                         tmp._end);  // [p + n, _end)
      swap(tmp);
    } else {
      // constructs at end
      std::uninitialized_copy(_end - n, _end, _end);

      // relocate [p, _end - n)
      std::copy_backward(p, _end - n, _end - 1);

      // insert
      std::fill_n(p, n, val);

      // update _end
      _end += n;
    }
    return iterator(p);
  }

  /**
   * @brief erases elements
   * @return typedef ft::vector_iterator<pointer> iterator
   *
   * @param pos - iterator
   * *pos - return *current (value current[0])
   * pos.base() - iterator_type current (vector_iterator)
   *
   * _end - pointer
   * end(void); function - return iterator(_end)
   *
   */
  iterator erase(iterator pos) {
    pointer _p = _begin + (pos - begin());

    if (_p != _end - 1) {
      _alloc.destroy(_p);
      // relocate
      std::copy(pos + 1, end(), pos);
      --_end;
    }
    return iterator(_p);
  }

  // [first, last)
  iterator erase(iterator first, iterator last) {
    difference_type n = last - first;
    pointer _first = _begin + (first - begin());
    pointer _last = _begin + (last - begin());

    if (first != last) {
      for (pointer _p = _first; _p < _last; _p++) {
        _alloc.destroy(_p);
      }
      // relocate
      std::copy(last, end(), first);
      _end -= n;
    }
    return iteraotr(p);
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
    _alloc.construct(_end, value);
    ++_end;
  }

  /**
   * @brief removes the last element
   */
  void pop_back(void) { _end = erase(_end); }

  /*
   * @brief changes the number of elements stored
   */
  void resize(size_type new_size, value_type value = value_type()) {
    if (new_size < size()) {
      _end = erase(begin() + new_size, end());
    } else {
      insert(_end, size() - new_size, val);  // included reallocate
    }
  }

  /**
   * @brief swaps the contents
   */
  void swap(vector& other) {
    _swap(_begin, other._begin);
    _swap(_end, other._end);
    _swap(_end_cap, other._end_cap);
  }

  // !SECTION 2-2-5
  // !SECTION 2-2

  // SECTION 2-3. Private Member Functions
 private:
  void _swap(T& a, T& b) {
    T tmp(a);
    a = b;
    b = tmp;
  }
};
// !SECTION 2

// SECTION 3. Non-member functions
/** SECTION 3-1. Relational operators
 * @brief Compares the contents of two vectors
 */
template <typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  // return rhs < lhs;
  return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(),
                                     lhs.end());
}

template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs > rhs);
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