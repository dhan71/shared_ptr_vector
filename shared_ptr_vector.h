#ifndef _shared_ptr_vector_h_
#define _shared_ptr_vector_h_

/**
 * shared_ptr_vector is a vector for shared pointers
 * author : dhan71@naver.com
 */
/**
*  @brief A standard container which offers fixed time access to
*  individual elements in any order.
*
*  @ingroup sequences
*
*  @tparam _Tp  Type of element.
*  @tparam _Alloc  Allocator type, defaults to allocator<_Tp>.
*
*  Meets the requirements of a <a href="tables.html#65">container</a>, a
*  <a href="tables.html#66">reversible container</a>, and a
*  <a href="tables.html#67">sequence</a>, including the
*  <a href="tables.html#68">optional sequence requirements</a> with the
*  %exception of @c push_front and @c pop_front.
*
*  In some terminology a shared_ptr_vector can be described as a dynamic
*  C-style array, it offers fast and efficient access to individual
*  elements in any order and saves the user from worrying about
*  memory and size allocation.  Subscripting ( @c [] ) access is
*  also provided as with C-style arrays.
*/

#include <vector>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>


template<typename _Tp>
class shared_ptr_vector
{
public:
  typedef std::vector<std::shared_ptr<_Tp> > _base_type;

  typedef _Tp       value_type;
  typedef _Tp*      data_type;
  typedef const _Tp* const_data_type;
  typedef std::shared_ptr<_Tp> shared_value_type;

  typedef typename _base_type::pointer pointer;
  typedef typename _base_type::const_pointer const_pointer;
  typedef typename _base_type::reference reference;
  typedef typename _base_type::const_reference const_reference;
  typedef typename _base_type::iterator iterator;
  typedef typename _base_type::const_iterator const_iterator;
  typedef typename _base_type::reverse_iterator reverse_iterator;
  typedef typename _base_type::const_reverse_iterator const_reverse_iterator;

  typedef typename _base_type::size_type size_type;
  typedef typename _base_type::difference_type difference_type;
  typedef typename _base_type::allocator_type allocator_type;

  friend class Tests;

public:
  // [23.2.4.1] construct/copy/destroy
  // (assign() and get_allocator() are also listed in this section)

  /**
   *  @brief  Creates a shared_ptr_vector with no elements.
   */
  shared_ptr_vector()
  { }

  /**
   *  @brief  Creates a shared_ptr_vector with no elements.
   *  @param  __a  An allocator object.
   */
  explicit
  shared_ptr_vector(const allocator_type& __a)
  : iList(__a)
  { }

  /**
   *  @brief  Creates a shared_ptr_vector with default constructed elements.
   *  @param  __n  The number of elements to initially create.
   *  @param  __a  An allocator.
   *
   *  This constructor fills the shared_ptr_vector with @a __n default
   *  constructed elements.
   */
  explicit
  shared_ptr_vector(size_type __n, const allocator_type& __a = allocator_type())
  : iList(__n, __a)
  {
  }

  /**
   *  @brief  Creates a shared_ptr_vector with copies of an exemplar element.
   *  @param  __n  The number of elements to initially create.
   *  @param  __value  An element to copy.
   *  @param  __a  An allocator.
   *
   *  This constructor fills the shared_ptr_vector with @a __n copies of @a __value.
   */
//shared_ptr_vector(size_type __n, const value_type& __value, const allocator_type& __a = allocator_type())
  shared_ptr_vector(size_type __n, const data_type& __value, const allocator_type& __a = allocator_type())
  : iList(__n, shared_value_type(__value), __a)
  {
  }
#if 0
  /**
   *  @brief  shared_ptr_vector copy constructor.
   *  @param  __x  A shared_ptr_vector of identical element and allocator types.
   *
   *  All the elements of @a __x are copied, but any unused capacity in
   *  @a __x  will not be copied
   *  (i.e. capacity() == size() in the new shared_ptr_vector).
   *
   *  The newly-created shared_ptr_vector uses a copy of the allocator object used
   *  by @a __x (unless the allocator traits dictate a different object).
   */
  shared_ptr_vector(const shared_ptr_vector& __x)
  : _iList(__x)
  {
  }

  /**
   *  @brief  shared_ptr_vector move constructor.
   *
   *  The newly-created shared_ptr_vector contains the exact contents of the
   *  moved instance.
   *  The contents of the moved instance are a valid, but unspecified
   *  shared_ptr_vector.
   */
  shared_ptr_vector(shared_ptr_vector&&) noexcept = default;

  /// Copy constructor with alternative allocator
  shared_ptr_vector(const shared_ptr_vector& __x, const allocator_type& __a)
  : _base_type(__x.size(), __a)
  {
  }

private:
  shared_ptr_vector(shared_ptr_vector&& __rv, const allocator_type& __m, true_type) noexcept
  : _base_type(__m, std::move(__rv))
  { }

  shared_ptr_vector(shared_ptr_vector&& __rv, const allocator_type& __m, false_type)
  : _base_type(__m)
  {
  }

public:
  /// Move constructor with alternative allocator
  shared_ptr_vector(shared_ptr_vector&& __rv, const allocator_type& __m)
  noexcept( noexcept( shared_ptr_vector(std::declval<shared_ptr_vector&&>(), std::declval<const allocator_type&>(), std::declval<typename _Alloc_traits::is_always_equal>())) )
  : shared_ptr_vector(std::move(__rv), __m, typename _Alloc_traits::is_always_equal{})
  { }

  /**
   *  @brief  Builds a shared_ptr_vector from an initializer list.
   *  @param  __l  An initializer_list.
   *  @param  __a  An allocator.
   *
   *  Create a shared_ptr_vector consisting of copies of the elements in the
   *  initializer_list @a __l.
   *
   *  This will call the element type's copy constructor N times
   *  (where N is @a __l.size()) and do no memory reallocation.
   */
  shared_ptr_vector(initializer_list<value_type> __l, const allocator_type& __a = allocator_type())
  : _base_type(__a)
  {
  }

  /**
   *  @brief  Builds a shared_ptr_vector from a range.
   *  @param  __first  An input iterator.
   *  @param  __last  An input iterator.
   *  @param  __a  An allocator.
   *
   *  Create a shared_ptr_vector consisting of copies of the elements from
   *  [first,last).
   *
   *  If the iterators are forward, bidirectional, or
   *  random-access, then this will call the elements' copy
   *  constructor N times (where N is distance(first,last)) and do
   *  no memory reallocation.  But if only input iterators are
   *  used, then this will do at most 2N calls to the copy
   *  constructor, and logN memory reallocations.
   */
  template<typename _InputIterator>
  shared_ptr_vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a = allocator_type())
  : iList(__a)
  {
  }
#endif

  /**
   *  The dtor only erases the elements, and note that if the
   *  elements themselves are pointers, the pointed-to memory is
   *  not touched in any way.  Managing the pointer is the user's
   *  responsibility.
   */
  ~shared_ptr_vector()
  {
  }
#if 0
public:
  /**
   *  @brief  shared_ptr_vector assignment operator.
   *  @param  __x  A shared_ptr_vector of identical element and allocator types.
   *
   *  All the elements of @a __x are copied, but any unused capacity in
   *  @a __x will not be copied.
   *
   *  Whether the allocator is copied depends on the allocator traits.
   */
  shared_ptr_vector&
  operator=(const shared_ptr_vector& __x)
  {
    iList = __x.iList;
    return *this;
  }

  /**
   *  @brief  shared_ptr_vector move assignment operator.
   *  @param  __x  A shared_ptr_vector of identical element and allocator types.
   *
   *  The contents of @a __x are moved into this shared_ptr_vector (without copying,
   *  if the allocators permit it).
   *  Afterwards @a __x is a valid, but unspecified shared_ptr_vector.
   *
   *  Whether the allocator is moved depends on the allocator traits.
   */
  shared_ptr_vector&
  operator=(shared_ptr_vector&& __x) noexcept(_Alloc_traits::_S_nothrow_move())
  {
    iList = __x.iList;
    return *this;
  }

  /**
   *  @brief  shared_ptr_vector list assignment operator.
   *  @param  __l  An initializer_list.
   *
   *  This function fills a shared_ptr_vector with copies of the elements in the
   *  initializer list @a __l.
   *
   *  Note that the assignment completely changes the shared_ptr_vector and
   *  that the resulting shared_ptr_vector's size is the same as the number
   *  of elements assigned.
   */
  shared_ptr_vector&
  operator=(initializer_list<value_type> __l)
  {
    iList = __l.iList;
    return *this;
  }

  /**
   *  @brief  Assigns a given value to a shared_ptr_vector.
   *  @param  __n  Number of elements to be assigned.
   *  @param  __val  Value to be assigned.
   *
   *  This function fills a shared_ptr_vector with @a __n copies of the given
   *  value.  Note that the assignment completely changes the
   *  shared_ptr_vector and that the resulting shared_ptr_vector's size is the same as
   *  the number of elements assigned.
   */
  void
  assign(size_type __n, const value_type& __val)
  {
    iList.assign(__n, __val);
  }

  /**
   *  @brief  Assigns a range to a shared_ptr_vector.
   *  @param  __first  An input iterator.
   *  @param  __last   An input iterator.
   *
   *  This function fills a shared_ptr_vector with copies of the elements in the
   *  range [__first,__last).
   *
   *  Note that the assignment completely changes the shared_ptr_vector and
   *  that the resulting shared_ptr_vector's size is the same as the number
   *  of elements assigned.
   */
  template<typename _InputIterator>
  void
  assign(_InputIterator __first, _InputIterator __last)
  {
    iList.assign(__first, __last);
  }

  /**
   *  @brief  Assigns an initializer list to a shared_ptr_vector.
   *  @param  __l  An initializer_list.
   *
   *  This function fills a shared_ptr_vector with copies of the elements in the
   *  initializer list @a __l.
   *
   *  Note that the assignment completely changes the shared_ptr_vector and
   *  that the resulting shared_ptr_vector's size is the same as the number
   *  of elements assigned.
   */
  void
  assign(initializer_list<value_type> __l)
  {
    iList.assign(__l);
  }


  // iterators
  /**
   *  Returns a read/write iterator that points to the first
   *  element in the shared_ptr_vector.  Iteration is done in ordinary
   *  element order.
   */
  iterator
  begin()
  {
    return iList.begin();
  }

  /**
   *  Returns a read-only (constant) iterator that points to the
   *  first element in the shared_ptr_vector.  Iteration is done in ordinary
   *  element order.
   */
  const_iterator
  begin() const
  {
    return iList.begin();
  }

  /**
   *  Returns a read/write iterator that points one past the last
   *  element in the shared_ptr_vector.  Iteration is done in ordinary
   *  element order.
   */
  iterator
  end()
  {
    return iList.end();
  }

  /**
   *  Returns a read-only (constant) iterator that points one past
   *  the last element in the shared_ptr_vector.  Iteration is done in
   *  ordinary element order.
   */
  const_iterator
  end() const
  {
    return iList.end();
  }

  /**
   *  Returns a read/write reverse iterator that points to the
   *  last element in the shared_ptr_vector.  Iteration is done in reverse
   *  element order.
   */
  reverse_iterator
  rbegin()
  {
    return iList.rbegin();
  }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to the last element in the shared_ptr_vector.  Iteration is done in
   *  reverse element order.
   */
  const_reverse_iterator
  rbegin() const
  {
    return iList.rbegin();
  }

  /**
   *  Returns a read/write reverse iterator that points to one
   *  before the first element in the shared_ptr_vector.  Iteration is done
   *  in reverse element order.
   */
  reverse_iterator
  rend()
  {
    return iList.rend();
  }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to one before the first element in the shared_ptr_vector.  Iteration
   *  is done in reverse element order.
   */
  const_reverse_iterator
  rend() const
  {
    return iList.rend();
  }

  /**
   *  Returns a read-only (constant) iterator that points to the
   *  first element in the shared_ptr_vector.  Iteration is done in ordinary
   *  element order.
   */
  const_iterator
  cbegin() const noexcept
  {
    return iList.cbegin();
  }

  /**
   *  Returns a read-only (constant) iterator that points one past
   *  the last element in the shared_ptr_vector.  Iteration is done in
   *  ordinary element order.
   */
  const_iterator
  cend() const noexcept
  {
    return iList.cend();
  }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to the last element in the shared_ptr_vector.  Iteration is done in
   *  reverse element order.
   */
  const_reverse_iterator
  crbegin() const noexcept
  {
    return iList.crbegin();
  }

  /**
   *  Returns a read-only (constant) reverse iterator that points
   *  to one before the first element in the shared_ptr_vector.  Iteration
   *  is done in reverse element order.
   */
  const_reverse_iterator
  crend() const noexcept
  {
    return iList.crend();
  }
#endif
  // [23.2.4.2] capacity
  /**  Returns the number of elements in the shared_ptr_vector.  */
  size_type
  size() const
  {
    return iList.size();
  }
#if 0
  /**  Returns the size() of the largest possible shared_ptr_vector.  */
  size_type
  max_size() const
  {
    return iList.max_size();
  }

  /**
   *  @brief  Resizes the shared_ptr_vector to the specified number of elements.
   *  @param  __new_size  Number of elements the shared_ptr_vector should contain.
   *
   *  This function will %resize the shared_ptr_vector to the specified
   *  number of elements.  If the number is smaller than the
   *  shared_ptr_vector's current size the shared_ptr_vector is truncated, otherwise
   *  default constructed elements are appended.
   */
  void
  resize(size_type __new_size)
  {
    iList.resize(__new_size);
  }

  /**
   *  @brief  Resizes the shared_ptr_vector to the specified number of elements.
   *  @param  __new_size  Number of elements the shared_ptr_vector should contain.
   *  @param  __x  Data with which new elements should be populated.
   *
   *  This function will %resize the shared_ptr_vector to the specified
   *  number of elements.  If the number is smaller than the
   *  shared_ptr_vector's current size the shared_ptr_vector is truncated, otherwise
   *  the shared_ptr_vector is extended and new elements are populated with
   *  given data.
   */
  void
  resize(size_type __new_size, const value_type& __x)
  {
    iList.resize(__new_size, __x);
  }

  /**  A non-binding request to reduce capacity() to size().  */
  void
  shrink_to_fit()
  {
    iList.shrink_to_fit();
  }

  /**
   *  Returns the total number of elements that the shared_ptr_vector can
   *  hold before needing to allocate more memory.
   */
  size_type
  capacity() const
  {
    return iList.capacity();
  }
#endif
  /**
   *  Returns true if the shared_ptr_vector is empty.  (Thus begin() would
   *  equal end().)
   */
  bool
  empty() const
  {
    return iList.empty();
  }
#if 0
  /**
   *  @brief  Attempt to preallocate enough memory for specified number of
   *          elements.
   *  @param  __n  Number of elements required.
   *  @throw  std::length_error  If @a n exceeds @c max_size().
   *
   *  This function attempts to reserve enough memory for the
   *  shared_ptr_vector to hold the specified number of elements.  If the
   *  number requested is more than max_size(), length_error is
   *  thrown.
   *
   *  The advantage of this function is that if optimal code is a
   *  necessity and the user can determine the number of elements
   *  that will be required, the user can reserve the memory in
   *  %advance, and thus prevent a possible reallocation of memory
   *  and copying of shared_ptr_vector data.
   */
  void
  reserve(size_type __n)
  {
    iList.reserve(__n);
  }

  // element access
  /**
   *  @brief  Subscript access to the data contained in the shared_ptr_vector.
   *  @param __n The index of the element for which data should be
   *  accessed.
   *  @return  Read/write reference to data.
   *
   *  This operator allows for easy, array-style, data access.
   *  Note that data access with this operator is unchecked and
   *  out_of_range lookups are not defined. (For checked lookups
   *  see at().)
   */
  reference
  operator[](size_type __n)
  {
    return iList[__n];
  }

  /**
   *  @brief  Subscript access to the data contained in the shared_ptr_vector.
   *  @param __n The index of the element for which data should be
   *  accessed.
   *  @return  Read-only (constant) reference to data.
   *
   *  This operator allows for easy, array-style, data access.
   *  Note that data access with this operator is unchecked and
   *  out_of_range lookups are not defined. (For checked lookups
   *  see at().)
   */
  const_reference
  operator[](size_type __n) const
  {
    return iList[__n];
  }

#endif
public:
  /**
   *  @brief  Provides access to the data contained in the shared_ptr_vector.
   *  @param __n The index of the element for which data should be
   *  accessed.
   *  @return  Read/write reference to data.
   *  @throw  std::out_of_range  If @a __n is an invalid index.
   *
   *  This function provides for safer data access.  The parameter
   *  is first checked that it is in the range of the shared_ptr_vector.  The
   *  function throws out_of_range if the check fails.
   */
  reference
  at(size_type __n)
  {
    return iList.at(__n);
  }

  /**
   *  @brief  Provides access to the data contained in the shared_ptr_vector.
   *  @param __n The index of the element for which data should be
   *  accessed.
   *  @return  Read-only (constant) reference to data.
   *  @throw  std::out_of_range  If @a __n is an invalid index.
   *
   *  This function provides for safer data access.  The parameter
   *  is first checked that it is in the range of the shared_ptr_vector.  The
   *  function throws out_of_range if the check fails.
   */
  const_reference
  at(size_type __n) const
  {
    return iList.at(__n);
  }

  /**
   *  Returns a read/write reference to the data at the first
   *  element of the shared_ptr_vector.
   */
  reference
  front()
  {
    return iList.front();
  }

  /**
   *  Returns a read-only (constant) reference to the data at the first
   *  element of the shared_ptr_vector.
   */
  const_reference
  front() const
  {
    return iList.front();
  }

  /**
   *  Returns a read/write reference to the data at the last
   *  element of the shared_ptr_vector.
   */
  reference
  back()
  {
    return iList.back();
  }

  /**
   *  Returns a read-only (constant) reference to the data at the
   *  last element of the shared_ptr_vector.
   */
  const_reference
  back() const
  {
    return iList.back();
  }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // DR 464. Suggestion for new member functions in standard containers.
  // data access
  /**
   *   Returns a pointer such that [data(), data() + size()) is a valid
   *   range.  For a non-empty shared_ptr_vector, data() == &front().
   */
  _Tp*
  data()
  {
    return iList.data();
  }

  const _Tp*
  data() const
  {
    return iList.data();
  }

  // [23.2.4.3] modifiers
  /**
   *  @brief  Add data to the end of the shared_ptr_vector.
   *  @param  __x  Data to be added.
   *
   *  This is a typical stack operation.  The function creates an
   *  element at the end of the shared_ptr_vector and assigns the given data
   *  to it.  Due to the nature of a shared_ptr_vector this operation can be
   *  done in constant time if the shared_ptr_vector has preallocated space
   *  available.
   */
  void
  push_back(const data_type& __x)
  {
    iList.push_back(shared_value_type(__x));
  }

  void
  push_back(data_type&& __x)
  {
    iList.push_back(shared_value_type(__x));
  }

  template <typename raw_type>
  void
  push_back(const raw_type& __x)
  {
    iList.push_back(shared_value_type( new raw_type(__x) ));
  }
#if 0
  template<typename... _Args>
  reference
  emplace_back(_Args&&... __args)
  {
    return iList.emplace_back(__args...);
  }
#endif
  /**
   *  @brief  Removes last element.
   *
   *  This is a typical stack operation. It shrinks the shared_ptr_vector by one.
   *
   *  Note that no data is returned, and if the last element's
   *  data is needed, it should be retrieved before pop_back() is
   *  called.
   */
  void
  pop_back()
  {
    iList.pop_back();
  }
#if 0
  /**
   *  @brief  Inserts an object in shared_ptr_vector before specified iterator.
   *  @param  __position  A const_iterator into the shared_ptr_vector.
   *  @param  __args  Arguments.
   *  @return  An iterator that points to the inserted data.
   *
   *  This function will insert an object of type T constructed
   *  with T(std::forward<Args>(args)...) before the specified location.
   *  Note that this kind of operation could be expensive for a shared_ptr_vector
   *  and if it is frequently used the user should consider using
   *  std::list.
   */
  template<typename... _Args>
  iterator
  emplace(const_iterator __position, _Args&&... __args)
  {
    return iList.implace(__position, __args...);
  }

  /**
   *  @brief  Inserts given value into shared_ptr_vector before specified iterator.
   *  @param  __position  A const_iterator into the shared_ptr_vector.
   *  @param  __x  Data to be inserted.
   *  @return  An iterator that points to the inserted data.
   *
   *  This function will insert a copy of the given value before
   *  the specified location.  Note that this kind of operation
   *  could be expensive for a shared_ptr_vector and if it is frequently
   *  used the user should consider using std::list.
   */
  iterator
  insert(const_iterator __position, const value_type& __x)
  {
    return iList.insert(__position, __x);
  }

  /**
   *  @brief  Inserts given rvalue into shared_ptr_vector before specified iterator.
   *  @param  __position  A const_iterator into the shared_ptr_vector.
   *  @param  __x  Data to be inserted.
   *  @return  An iterator that points to the inserted data.
   *
   *  This function will insert a copy of the given rvalue before
   *  the specified location.  Note that this kind of operation
   *  could be expensive for a shared_ptr_vector and if it is frequently
   *  used the user should consider using std::list.
   */
  iterator
  insert(const_iterator __position, value_type&& __x)
  {
    return iList.insert(__position, __x);
  }

  /**
   *  @brief  Inserts an initializer_list into the shared_ptr_vector.
   *  @param  __position  An iterator into the shared_ptr_vector.
   *  @param  __l  An initializer_list.
   *
   *  This function will insert copies of the data in the
   *  initializer_list @a l into the shared_ptr_vector before the location
   *  specified by @a position.
   *
   *  Note that this kind of operation could be expensive for a
   *  shared_ptr_vector and if it is frequently used the user should
   *  consider using std::list.
   */
  iterator
  insert(const_iterator __position, initializer_list<value_type> __l)
  {
    return iList.insert(__position, __l);
  }

  /**
   *  @brief  Inserts a number of copies of given data into the shared_ptr_vector.
   *  @param  __position  A const_iterator into the shared_ptr_vector.
   *  @param  __n  Number of elements to be inserted.
   *  @param  __x  Data to be inserted.
   *  @return  An iterator that points to the inserted data.
   *
   *  This function will insert a specified number of copies of
   *  the given data before the location specified by @a position.
   *
   *  Note that this kind of operation could be expensive for a
   *  shared_ptr_vector and if it is frequently used the user should
   *  consider using std::list.
   */
  iterator
  insert(const_iterator __position, size_type __n, const value_type& __x)
  {
    return iList.insert(__position, __n, __x);
  }

  /**
   *  @brief  Inserts a range into the shared_ptr_vector.
   *  @param  __position  A const_iterator into the shared_ptr_vector.
   *  @param  __first  An input iterator.
   *  @param  __last   An input iterator.
   *  @return  An iterator that points to the inserted data.
   *
   *  This function will insert copies of the data in the range
   *  [__first,__last) into the shared_ptr_vector before the location specified
   *  by @a pos.
   *
   *  Note that this kind of operation could be expensive for a
   *  shared_ptr_vector and if it is frequently used the user should
   *  consider using std::list.
   */
  template<typename _InputIterator>
  iterator
  insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
  {
    return iList.insert(__position, __first, __last);
  }

  /**
   *  @brief  Remove element at given position.
   *  @param  __position  Iterator pointing to element to be erased.
   *  @return  An iterator pointing to the next element (or end()).
   *
   *  This function will erase the element at the given position and thus
   *  shorten the shared_ptr_vector by one.
   *
   *  Note This operation could be expensive and if it is
   *  frequently used the user should consider using std::list.
   *  The user is also cautioned that this function only erases
   *  the element, and that if the element is itself a pointer,
   *  the pointed-to memory is not touched in any way.  Managing
   *  the pointer is the user's responsibility.
   */
  iterator
  erase(const_iterator __position)
  {
    return iList.erase __position;
  }

  /**
   *  @brief  Remove a range of elements.
   *  @param  __first  Iterator pointing to the first element to be erased.
   *  @param  __last  Iterator pointing to one past the last element to be
   *                  erased.
   *  @return  An iterator pointing to the element pointed to by @a __last
   *           prior to erasing (or end()).
   *
   *  This function will erase the elements in the range
   *  [__first,__last) and shorten the shared_ptr_vector accordingly.
   *
   *  Note This operation could be expensive and if it is
   *  frequently used the user should consider using std::list.
   *  The user is also cautioned that this function only erases
   *  the elements, and that if the elements themselves are
   *  pointers, the pointed-to memory is not touched in any way.
   *  Managing the pointer is the user's responsibility.
   */
  iterator
  erase(const_iterator __first, const_iterator __last)
  {
    return iList.erase();
  }

  /**
   *  @brief  Swaps data with another shared_ptr_vector.
   *  @param  __x  A shared_ptr_vector of the same element and allocator types.
   *
   *  This exchanges the elements between two shared_ptr_vectors in constant time.
   *  (Three pointers, so it should be quite fast.)
   *  Note that the global std::swap() function is specialized such that
   *  std::swap(v1,v2) will feed to this function.
   *
   *  Whether the allocators are swapped depends on the allocator traits.
   */
  void
  swap(shared_ptr_vector& __x)
  {
    iList.swap(__x.iList);
  }

  /**
   *  Erases all the elements.  Note that this function only erases the
   *  elements, and that if the elements themselves are pointers, the
   *  pointed-to memory is not touched in any way.  Managing the pointer is
   *  the user's responsibility.
   */
  void
  clear()
  { iList.clear(); }
#endif
private:
  _base_type iList;
};

#if __cpp_deduction_guides >= 201606
template<typename _InputIterator, typename _ValT
 = typename iterator_traits<_InputIterator>::value_type,
   typename _Allocator = allocator<_ValT>,
   typename = _RequireInputIter<_InputIterator>,
   typename = _RequireAllocator<_Allocator>>
shared_ptr_vector(_InputIterator, _InputIterator, _Allocator = _Allocator())
  -> shared_ptr_vector<_ValT, _Allocator>;
#endif

#if 0
/**
*  @brief  shared_ptr_vector equality comparison.
*  @param  __x  A shared_ptr_vector.
*  @param  __y  A shared_ptr_vector of the same type as @a __x.
*  @return  True iff the size and elements of the shared_ptr_vectors are equal.
*
*  This is an equivalence relation.  It is linear in the size of the
*  shared_ptr_vectors.  shared_ptr_vectors are considered equivalent if their sizes are equal,
*  and if corresponding elements compare equal.
*/
template<typename _Tp, typename _Alloc>
inline bool
operator==(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return (__x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin())); }

/**
*  @brief  shared_ptr_vector ordering relation.
*  @param  __x  A shared_ptr_vector.
*  @param  __y  A shared_ptr_vector of the same type as @a __x.
*  @return  True iff @a __x is lexicographically less than @a __y.
*
*  This is a total ordering relation.  It is linear in the size of the
*  shared_ptr_vectors.  The elements must be comparable with @c <.
*
*  See std::lexicographical_compare() for how the determination is made.
*/
template<typename _Tp, typename _Alloc>
inline bool
operator<(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }

/// Based on operator==
template<typename _Tp, typename _Alloc>
inline bool
operator!=(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return !(__x == __y); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return __y < __x; }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator<=(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return !(__y < __x); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>=(const shared_ptr_vector<_Tp, _Alloc>& __x, const shared_ptr_vector<_Tp, _Alloc>& __y)
{ return !(__x < __y); }

/// See std::shared_ptr_vector::swap().
template<typename _Tp, typename _Alloc>
inline void
swap(shared_ptr_vector<_Tp, _Alloc>& __x, shared_ptr_vector<_Tp, _Alloc>& __y)
_GLIBCXX_NOEXCEPT_IF(noexcept(__x.swap(__y)))
{ __x.swap(__y); }

_GLIBCXX_END_NAMESPACE_CONTAINER

#if __cplusplus >= 201703L
namespace __detail::__variant
{
template<typename> struct _Never_valueless_alt; // see <variant>

// Provide the strong exception-safety guarantee when emplacing a
// shared_ptr_vector into a variant, but only if move assignment cannot throw.
template<typename _Tp, typename _Alloc>
  struct _Never_valueless_alt<_GLIBCXX_STD_C::shared_ptr_vector<_Tp, _Alloc>>
  : std::is_nothrow_move_assignable<_GLIBCXX_STD_C::shared_ptr_vector<_Tp, _Alloc>>
  { };
}  // namespace __detail::__variant
#endif // C++17

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#endif

template <typename _Tp>
std::string
to_string(const shared_ptr_vector<_Tp>& __x)
{
  std::stringstream ss;
  ss << "[ ";
//for (auto i = __x.begin(); i != __x.end(); ++i)
  for (size_t i = 0; i < __x.size(); ++i)
  {
//  ss << **i << " ";
    ss << *(__x.at(i).get()) << " ";
  }
  ss << "]";
  return ss.str();
}

template <typename _Tp>
std::ostream&
operator<<(std::ostream& os, const shared_ptr_vector<_Tp>& __x)
{
  os << "[ ";
//for (auto i = __x.begin(); i != __x.end(); ++i)
  for (size_t i = 0; i < __x.size(); ++i)
  {
//  ss << **i << " ";
    os << *(__x.at(i).get()) << " ";
  }
  os << "]";
  return os;
}

#endif /* _shared_ptr_vector_h_ */
