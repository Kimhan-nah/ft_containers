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

namespace ft {

/** SECTION 0. vector_iterator
 * @brief random_access_iterator (normal_iterator in GNU)
 *
 * @tparam Iter
 * @tparam Container
 *
 * Iterator invalidation : swap, clear, operator=, assign, earse ...
 */
template <typename Iter>
struct vector_iterator {
  // CHECK Consider inherit iterator_traits to vector_iterator
 public:
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;

  // TODO modify vector_iterator constructor
  // vector_iterator() : iterator() {}
  // vector_iterator(const) {}
};

// specialization
template <typename Iter>
struct vector_iterator<const Iter> {
 public:
  typedef typename iterator_traits<Iter>::difference_type difference_type;
  typedef typename iterator_traits<Iter>::value_type value_type;
  typedef typename iterator_traits<Iter>::pointer pointer;
  typedef typename iterator_traits<Iter>::reference reference;
  typedef typename iterator_traits<Iter>::iterator_category iterator_category;

  // TODO vector_iterator
  // vector_iterator() : iterator() {}
  // vector_iterator(const) {}
};
// !SECTION 0

/** SECTION 1. vector_base
 * @brief RAII pattern for resource management
 *
 */
template <typename T, typename Allocator = std::allocator<T> >
class vector_base {
 protected:
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::pointer pointer;
  // std::size_t
  typedef typename allocator_type::size_t size_t;
  // std::ptrdiff_t
  typedef typename allocator_type::difference_type difference_type;

  allocator_type _alloc;
  pointer _begin;    // _m_start (gcc), _begin(llvm)
  pointer _end;      // _m_finish
  pointer _end_cap;  // _m_end_of_storage?

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

  // random_access_iterator to value_type
  typedef vector_iterator<pointer> iterator;
  typedef vector_iterator<const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  // !SECTION 2-1

  // SECTION 2-2. Member Functions
 public:
  // SECTION 2-2-1. constructor, allocator
  // NOTE (constructor), (destructor), operator=, assign, get_allocator
  // vector(void) : _Base(void) {}
  // 1. default
  explicit vector(const allocator_type& alloc = allocator_type())
      : _Base(alloc) {}
  // 2. fill
  explicit vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _Base(count, alloc) {
    // std::uninitailized_fill();
  }
  // 3. range
  template <typename InputIt>
  vector(InputIt first, InputIt last,
         const allocator_type& alloc = allocator_type())
      : _Base(alloc) {}
  // 4. copy
  vector(const vector& other) {}

  ~vector(void);

  vector& operator=(const vector& ref);

  void assign(size_type count, const value_type& value);
  template <typename InputIt>
  void assign(InputIt first, InputIt last);

  allocator_type get_allocator() const;
  // !SECTION 2-2-1

  // SECTION 2-2-2. Element access
  // NOTE at, operator[], front, back, data
  // !SECTION 2-2-2

  // SECTION 2-2-3. Iterastors
  // NOTE begin, end, rbegin, rend
  // !SECTION 2-2-3

  // SECTION 2-2-4. Capacity
  // NOTE empty, size, max_size, reserve, capacity
  // !SECTION 2-2-4

  // SECTION 2-2-5. Modifiers
  // NOTE clear, insert, erase, push_back, pop_back, resize, swap
  // !SECTION 2-2-5
};
// !SECTION 2-2
// !SECTION 2

// SECTION 3. Non-member functions
/** SECTION 3-1. Relational operators
 * @brief Compares the contents of two vectors
 *
 * @tparam T
 * @tparam Alloc
 * @param lhs vector of left-hand side of the operator whose content to compare
 * @param rhs vector of right-hand side of the operator whose content to compare
 * @return true
 * @return false
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