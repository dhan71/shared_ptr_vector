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

template<typename _Tp, typename _Alloc = std::allocator<std::shared_ptr<_Tp> > >
class shared_ptr_vector
{
public:
  typedef std::vector<std::shared_ptr<_Tp>, _Alloc> _vector_type;

  typedef _Tp                  value_type;
  typedef _Tp*                 data_type;
  typedef const _Tp*           const_data_type;
  typedef std::shared_ptr<_Tp> shared_data_type;

  typedef typename _vector_type::pointer                pointer;
  typedef typename _vector_type::const_pointer          const_pointer;
  typedef typename _vector_type::reference              reference;
  typedef typename _vector_type::const_reference        const_reference;
  typedef typename _vector_type::iterator               iterator;
  typedef typename _vector_type::const_iterator         const_iterator;
  typedef typename _vector_type::reverse_iterator       reverse_iterator;
  typedef typename _vector_type::const_reverse_iterator const_reverse_iterator;

  typedef typename _vector_type::size_type       size_type;
  typedef typename _vector_type::difference_type difference_type;
  typedef typename _vector_type::allocator_type  allocator_type;

  friend class Tests;

#define _DEBUG_OUT
#ifdef _DEBUG_OUT
#define _OUT(m) std::cout << m << std::endl
#else
#define _OUT(m)
#endif

public:
  // [23.2.4.1] construct/copy/destroy
  // (assign() and get_allocator() are also listed in this section)

  /**
   *  @brief  Creates a shared_ptr_vector with no elements.
   */
  shared_ptr_vector()
  {
    _OUT(" + shared_ptr_vector() default ctor called");
  }

  /**
   *  @brief  Creates a shared_ptr_vector with no elements.
   *  @param  __a  An allocator object.
   */
  explicit
  shared_ptr_vector(const allocator_type& __a)
  : iList(__a)
  {
    _OUT(" + shared_ptr_vector(const allocator_type& __a)) ctor called");
  }

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
    _OUT(" + shared_ptr_vector(size_type __n, cconst allocator_type& __a)) ctor called");
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
  : iList(__n, shared_data_type(__value), __a)
  {
    _OUT(" + shared_ptr_vector(size_type __n, const data_type& __value, ccconst allocator_type& __a)) ctor called");
  }

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
  : iList(__x.iList)
  {
    _OUT(" + shared_ptr_vector(const shared_ptr_vector& __x) ctor called");
  }

  /**
   *  @brief  shared_ptr_vector move constructor.
   *
   *  The newly-created shared_ptr_vector contains the exact contents of the
   *  moved instance.
   *  The contents of the moved instance are a valid, but unspecified
   *  shared_ptr_vector.
   */
//shared_ptr_vector(shared_ptr_vector&&) noexcept = default;
  shared_ptr_vector(shared_ptr_vector&& __x)
  : iList(std::move(__x.iList))
  {
  }

  /// Copy constructor with alternative allocator
  shared_ptr_vector(const shared_ptr_vector& __x, const allocator_type& __a)
  : iList(__x.List, __a)
  {
    _OUT(" + shared_ptr_vector(const shared_ptr_vector& __x, const allocator_type& __a)) ctor called");
  }

public:
  /// Move constructor with alternative allocator
  shared_ptr_vector(shared_ptr_vector&& __rv, const allocator_type& __m)
//noexcept( noexcept( shared_ptr_vector(std::declval<shared_ptr_vector&&>(), std::declval<const allocator_type&>(), std::declval<typename _Alloc_traits::is_always_equal>())) )
  : iList(std::move(__rv.iList), __m)
  {
  }

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
//shared_ptr_vector(initializer_list<value_type> __l, const allocator_type& __a = allocator_type())
  shared_ptr_vector(std::initializer_list<data_type> __l, const allocator_type& __a = allocator_type())
  : iList(__a)
  {
    _OUT(" + shared_ptr_vector(std::initializer_list<data_type> __l, const allocator_type& __a) ctor called");
    iList.reserve(__l.size());
    //for (auto i : __l)
    //  this->push_back(i);
    for (auto i = __l.begin(); i != __l.end(); ++i)
      this->push_back(*i);
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
    _OUT(" + shared_ptr_vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a) ctor called");
    iList.reserve(__last - __first);
    for ( ; __first != __last; ++__first)
      this->push_back(*__first);
  }

  /**
   *  The dtor only erases the elements, and note that if the
   *  elements themselves are pointers, the pointed-to memory is
   *  not touched in any way.  Managing the pointer is the user's
   *  responsibility.
   */
  ~shared_ptr_vector()
  {
    _OUT(" - ~shared_ptr_vector() dtor called");
  }

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
    _OUT(" + operator=(const shared_ptr_vector& __x) called");
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
  operator=(shared_ptr_vector&& __x) //noexcept(_vector_type::_Alloc_traits::_S_nothrow_move())
  {
    _OUT(" + operator=(const shared_ptr_vector&& __x) noexcept called");
    iList = std::move(__x.iList);
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
  operator=(std::initializer_list<data_type> __l)
  {
    _OUT(" + operator=(std::initializer_list<data_type> __l) called");
    iList.reserve(__l.size());
    //for (auto i : __l)
    //  this->push_back(i);
    for (auto i = __l.begin(); i != __l.end(); ++i)
      this->push_back(*i);
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
  assign(size_type __n, const data_type& __val)
  {
    _OUT(" * assign(size_type __n, const data_type& __val) called");
    iList.assign(__n, shared_data_type(__val));
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
    _OUT(" * assign(_InputIterator __first, _InputIterator __last) called");
    for ( ; __first != __last; ++__first)
      this->push_back(*__first);
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
  assign(std::initializer_list<data_type> __l)
  {
    _OUT(" * assign(std::initializer_list<data_type> __l) called");
    this->assign(__l.begin(), __l.end());
  }

public:
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

  // [23.2.4.2] capacity
  /**  Returns the number of elements in the shared_ptr_vector.  */
  size_type
  size() const
  {
    return iList.size();
  }

public:
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
    _OUT(" * resize(size_type __new_size) called");
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
  resize(size_type __new_size, const data_type& __x)
  {
    _OUT(" * resize(size_type __new_size, const value_type& __x) called");
    iList.resize(__new_size, shared_data_type(__x));
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

  /**
   *  Returns true if the shared_ptr_vector is empty.  (Thus begin() would
   *  equal end().)
   */
  bool
  empty() const
  {
    return iList.empty();
  }

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

public:
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
  reference
  at(size_type __n, const data_type& __x)
  {
    iList.at(__n) = shared_data_type(__x);
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
//_Tp*
//data()
//{
//  return iList.data();
//}

//const _Tp*
//data() const
//{
//  return iList.data();
//}

public:
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
    iList.push_back(shared_data_type(__x));
  }

  void
  push_back(data_type&& __x)
  {
    iList.push_back(shared_data_type(__x));
  }

  // my utility function for value_type
  void
  push_back(const value_type& __x)
  {
    iList.push_back(shared_data_type( new value_type(__x) ));
  }

  template<typename... _Args>
  reference
  emplace_back(_Args&&... __args)
  {
    this->push_back(new _Tp(__args...));
    return this->back();
  }

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

public:
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
    //return iList.implace(__position, __args...);
    return iList.insert(__position, shared_data_type(new _Tp(__args...)));
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
  insert(const_iterator __position, const data_type& __x)
  {
    _OUT(" * insert(const_iterator __position, const data_type& __x) called");
    return iList.insert(__position, shared_data_type(__x));
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
  insert(const_iterator __position, data_type&& __x)
  {
    //return iList.insert(__position, __x);
    _OUT(" * insert(const_iterator __position, value_type&& __x) called");
    return iList.insert(__position, shared_data_type(__x));
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
  insert(const_iterator __position, std::initializer_list<data_type> __l)
  {
    return this->insert(__position, __l.begin(), __l.end());
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
  insert(const_iterator __position, size_type __n, const data_type& __x)
  {
    return iList.insert(__position, __n, shared_data_type(__x));
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
    _OUT(" * insert(const_iterator __position, _InputIterator __first, _InputIterator __last) called");
    //return iList.insert(__position, __first, __last);
    difference_type d = end() - __position;
    size_type n = std::distance(__first, __last);
    resize(size() + n);
    for (auto i = d; __first != __last; ++__first, ++i)
    {
      *(begin() + i) = shared_data_type(*__first);
    }
    return begin() + d;
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
   *
   *  @Note After this operation, the data at __position is deleted.
   *        After this operation, don't use the result iterator.
   */
  iterator
  erase(const_iterator __position)
  {
    return iList.erase(__position);
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
   *
   *  @Note After this operation, the data at __position is deleted.
   *        After this operation, don't use the result iterator.
   */
  iterator
  erase(const_iterator __first, const_iterator __last)
  {
    return iList.erase(__first, __last);
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

public:
  struct shared_ptr_data_equal
  {
    shared_ptr_data_equal(const data_type& __x)
    : iData(__x)
    { }

    bool operator()(const shared_data_type& val) const
    {
      return iData == val.get();
    }

  private:
    const data_type iData;
  };
  struct shared_ptr_value_equal
  {
    shared_ptr_value_equal(const value_type& __x)
    : iData(__x)
    { }

    bool operator()(const shared_data_type& val) const
    {
      if (val.get())
        return *val.get() == iData;
      else
        return false;
    }

  private:
    const value_type iData;
  };
  /**
   *  NULL is last element
   */
  struct shared_ptr_value_less
  {
    bool operator()(const shared_data_type& lhs, const shared_data_type& rhs) const
    {
      if (lhs.get() && rhs.get())
        return *lhs.get() < *rhs.get();
      else if (lhs.get())
        return true;
      else
        return false;
    }
  };

  /**
   *  @brief  output the elements of the shared_ptr_vector to ostream.
   *  @param  os   A output stream.
   *  @param  __x  A shared_ptr_vector.
   *  @return  os(input ostreeam)
   *
   *  This outpus the element of the shared_ptr_vector to ostream.
   *  The elements must have << operation.
   */
  void
  sort()
  {
   std::sort(begin(), end(), shared_ptr_value_less());
  }

  /*
  template <typename _Cmp>
  struct ElemCmp
  {
    bool operator()(const shared_data_type& lhs, const shared_data_type& rhs) const
    {
      return cmp(lhs.get(), rhs.get());
    }
  private:
    _Cmp cmp;
  }
  template <typename _Cmp>
  void
  sort(_Cmp __c)
  {
   std::sort(begin(), end(), ElemCmp<_Cmp>());
  }
  */

  /**
   *  @brief  find the position where __x is.
   *  @param  __x  A pointer
   *  @return  iterator where __x is
   *
   */
  iterator
  find(const data_type& __x)
  {
    return std::find_if(begin(), end(), shared_ptr_data_equal(__x));
  }
  const_iterator
  find(const data_type& __x) const
  {
    return std::find_if(begin(), end(), shared_ptr_data_equal(__x));
  }

  iterator
  find_value(const value_type& __x)
  {
    return std::find_if(begin(), end(), shared_ptr_value_equal(__x));
  }
  const_iterator
  find_value(const value_type& __x) const
  {
    return std::find_if(begin(), end(), shared_ptr_value_equal(__x));
  }
  iterator
  find_value(const data_type& __x)
  {
    if (__x)
      return std::find_if(begin(), end(), shared_ptr_value_equal(*__x));
    else
      return end();
  }
  const_iterator
  find_value(const data_type& __x) const
  {
    if (__x)
      return std::find_if(begin(), end(), shared_ptr_value_equal(*__x));
    else
      return end();
  }

  /**
   *  @brief  find iterator where __c is true.
   *  @param  __c  A compare object - compare values
   *  @return  iterator where __c is true.
   *
   */
  template <typename _Cmp>
  iterator
  find_if_value(const _Cmp& __c)
  {
    for (auto i = begin(); i != end(); ++i)
    {
      if (*i && __c(**i))
      {
        return i;
      }
    }
    return end();
  }

private:
  /**
   * vector which contains shared_ptr
   */
  _vector_type iList;
};

#if __cpp_deduction_guides >= 201606
/*
template<typename _InputIterator, typename _ValT
 = typename iterator_traits<_InputIterator>::value_type,
   typename _Allocator = allocator<_ValT>,
   typename = _RequireInputIter<_InputIterator>,
   typename = _RequireAllocator<_Allocator>>
shared_ptr_vector(_InputIterator, _InputIterator, _Allocator = _Allocator())
  -> shared_ptr_vector<_ValT, _Allocator>;
*/
#endif

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
{
//return (__x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin()));
  if (__x.size() != __y.size())
    return false;
  auto xe = __x.end();
  auto xb = __x.begin();
  auto yb = __y.begin();
  for ( ; xb != xe; ++xb, ++yb)
  {
    if ( !(*xb->get() == *yb->get()) )
      return false;
  }
  return true;
}

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
{
//return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
  auto xe = __x.end();
  auto ye = __y.end();
  auto xb = __x.begin();
  auto yb = __y.begin();
  for ( ; (xb != xe) && (yb != ye); ++xb, ++yb)
  {
    if ( (*xb->get() < *yb->get()) )
      return true;
    if ( (*yb->get() < *xb->get()) )
      return false;
  }
  if ( (xb == xe) && (yb == ye) )
    return false;
  if (xb == xe) 
    return true;
  return false;
}

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
//_GLIBCXX_NOEXCEPT_IF(noexcept(__x.swap(__y)))
{ __x.swap(__y); }


/**
*  @brief  convert the elements of the shared_ptr_vector to string.
*  @param  __x  A shared_ptr_vector.
*  @return  string representing shared_ptr_vector
*
*  This converts shared_ptr_vector to string.
*  The elements must have << operation.
*/
template <typename _Tp, typename _Alloc>
std::string
to_string(const shared_ptr_vector<_Tp, _Alloc>& __x)
{
  std::stringstream ss;
  ss << "[ ";
  for (auto i = __x.begin(); i != __x.end(); ++i)
  {
    if (*i)
      ss << **i << " ";
    else
      ss << "NULL ";
  }
  ss << "]";
  return ss.str();
}

/**
*  @brief  output the elements of the shared_ptr_vector to ostream.
*  @param  os   A output stream.
*  @param  __x  A shared_ptr_vector.
*  @return  os(input ostreeam)
*
*  This outpus the element of the shared_ptr_vector to ostream.
*  The elements must have << operation.
*/
template <typename _Tp, typename _Alloc>
std::ostream&
operator<<(std::ostream& os, const shared_ptr_vector<_Tp, _Alloc>& __x)
{
  os << "[ ";
  for (auto i = __x.begin(); i != __x.end(); ++i)
  {
    if (*i)
      os << **i << " ";
    else
      os << "NULL ";
  }
  os << "]";
  return os;
}

/**
*  @brief  output the elements of the shared_ptr_vector to ostream.
*  @param  os   A output stream.
*  @param  __x  A shared_ptr_vector.
*  @return  os(input ostreeam)
*
*  This outpus the element of the shared_ptr_vector to ostream.
*  The elements must have << operation.
*/
template <typename _Tp, typename _Alloc>
void
sort(shared_ptr_vector<_Tp, _Alloc>& __x)
{
  typedef typename shared_ptr_vector<_Tp, _Alloc>::shared_ptr_value_less shared_ptr_value_less;
  std::sort(__x.begin(), __x.end(), shared_ptr_value_less());
}


#endif /* _shared_ptr_vector_h_ */

