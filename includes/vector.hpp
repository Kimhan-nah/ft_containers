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
  // : allocator_type(alloc), _begin(NULL), _end(NULL), _end_cap(NULL) {}
  explicit vector_base(size_type count, const allocator_type& alloc)
      : _alloc(alloc),
        _begin(_alloc.allocator(count)),  // allocate & return pointer
        _end(_begin),
        _end_cap(_begin + count) {}
  ~vector_base(void) {
    // TODO destroy() & deallocate()
    _alloc.deallocate(_begin, _end_cap - _begin);
  }
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
// CHECK private || protected || public
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
  typedef typename _Base::difference_type;

  typedef typename _Base::_alloc _alloc;
  typedef typename _Base::_begin _begin;
  typedef typename _Base::_end _end;
  typedef typename _Base::_end_cap _end_cap;

  typedef ft::vector_iterator<pointer> iterator;
  typedef ft::vector_iterator<const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // !SECTION 2-1

  // SECTION 2-2. Member Functions
 public:
  // SECTION 2-2-1. constructors
  // NOTE Exception Safety : Strong guarantee <- RAII
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

  ~vector(void) {}

  // TODO modify operator=
  vector& operator=(const vector& other);

  // assign() : fill version
  void assign(size_type count, const value_type& value) {
    clear();
    // CHECK distance ?
    if (_end_cap - _end < count) {
      // TODO reallocate
    } else {
      std::uninitialized_fill_n(_begin, count, value);
      _end += count;
    }
  }

  // assign() : range version
  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    // CHECK distance??
    if (_end_cap - _end < count) {
      // TODO reallocate
    } else {
      _end = std::uninitialized_copy(first, last, _begin);
    }
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
  bool empty(void) const {
    // return size() == 0;
    return _begin == _end;
  }

  /**
   * @brief returns the number of elements
   * @exception No-Throw guarantee
   */
  size_type size(void) const { return _end - _begin; }

  /**
   * @brief returns the maximum possible number of elements
   * @exception No-Throw guarantee
   * CHECK allocator.max_size() throw ??
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
    if (new_cap > capacity()) {
      // reallocate
    }
  }

  size_type capacity(void) const { return _end_cap - _begin; }

  // !SECTION 2-2-4

  // SECTION 2-2-5. Modifiers
  // NOTE clear, insert, erase, push_back, pop_back, resize, swap

  /**
   * @brief clears the contents
   * @note erases all elements from the container
   */
  void clear(void) {}

  /**
   * @brief inserts elements
   *
   */
  void insert(void) {}

  /**
   * @brief erases elements
   */
  iterator erase(iterator pos) {
    if (*pos == _end) {
      return end();
    }
    _alloc.destroy(*pos);
    // relocation
  }
  iterator erase(iterator first, iterator last) {
    if (*last == end()) {
      // prior to removal
      // updated end() iterator is returned
    }
  }

  /**
   * @brief adds an element to the end
   *
   * @param value
   */
  void push_back(const value_type& value);

  /**
   * @brief removes the last element
   *
   */
  void pop_back(void);

  /**
   * @brief changes the number of elements stored
   *
   * @param count
   * @param value
   */
  void resize(size_type count, value_type value = value_type());

  /**
   * @brief swaps the contents
   *
   * @param other
   */
  void swap(vector& other);

  // !SECTION 2-2-5
};
// !SECTION 2-2
// !SECTION 2

// SECTION 3. Non-member functions
/** SECTION 3-1. Relational operators
 * @brief Compares the contents of two vectors
 */
template <typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
// !SECTION 3-1

// SECTION 3-2. swap function
template <typename T, typename Alloc>
void swap(vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs);
// !SECTION 3-2

// !SECTION 3
}  // namespace ft

#endif  // VECTOR_HPP