#ifndef CSHIFT_LWF_COLLECTION_ASSOCIATIVE_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_ASSOCIATIVE_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Pair.h"
#include "LWF/Collection/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Associative {

template <typename ValueType,
          typename KeyType,
          typename KeyComparer,
          Bool multiKey,
          typename Allocator >
struct Container
  : LWF::Collection::Traits::Container<ValueType, Allocator>,
    KeyComparer
{
  private: typedef
    LWF::Collection::Traits::Container<ValueType, Allocator> Base;
  public:

  typedef KeyType     Key;
  typedef typename Base::Type Type;
  typedef KeyComparer Comparer;
  static const Bool multi = multiKey;
  struct Insert;

  Void swap(Container &container) {
    LWF::swap<Comparer>(*this, container);
    Base::swap(container);
  }

  Comparer &comparer() { return *this; }
  const Comparer &comparer() const { return *this; }

  Container(const Comparer &comparer, const Allocator &allocator)
    : Base(allocator), Comparer(comparer) {}

  Container(const Allocator &allocator) : Base(allocator) {}

  struct Insert { template <typename Iterator> struct Result; };
};

template <typename T1, typename T2, typename T3, Bool v, typename T4>
template <typename Iterator>
struct Container<T1, T2, T3, v, T4>::Insert::Result
  : LWF::Pair<Iterator, Bool>
{
  private: typedef  LWF::Pair<Iterator, Bool> Base; public:

  template <typename U>
  Bool operator == (const U &u) const { return Base::first() == u; }
  template <typename U>
  Bool operator != (const U &u) const { return !(*this == u); }

  Bool operator == (const Bool &isNew) const { return isNew == *this; }
  Bool operator != (const Bool &isNew) const { return !(*this == isNew); }

  const Iterator &iterator() const { return Base::first(); }
  Iterator &iterator() { return Base::first(); }

  operator const Iterator &() const { return iterator(); }
  operator Iterator &() { return iterator(); }

  const Bool &New() const { return Base::second(); }
  Bool &New() { return Base::second(); }

  operator const Bool &() const { return New(); }
  operator Bool &() { return New(); }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Result(typename Base::First::Rvalue::Reference first,
         typename Base::Second::Rvalue::Reference second = True)
    : Base(first, second) {}
  #else // !C++11
  Result(typename Base::First::Reference first,
         typename Base::Second::Reference second = True)
    : Base(first, second){}
  #endif // !C++11

  #if PLATFORM_COMPILER_RVALUE_REFERENCE

  Result(Result &&result) : Base(LWF::Forward::reference<Base>(result)) {}
  Result(Base &&base) : Base(LWF::Forward::reference<Base>(base)) {}

  template <typename U>
  Result(Result<U> &&result)
    : Base(LWF::Forward::reference<Result<U> >(result)) {}
  template <typename U>
  Result(LWF::Pair<U, Bool> &&base)
    : Base(LWF::Forward::reference<LWF::Pair<U, Bool> >(base)) {}

  #endif // C++11

  Result(const Result &result) : Base(result) {}
  Result(const Base &base) : Base(base) {}

  template <typename U>
  Result(const Result<U> &result) : Base(result) {}
  template <typename U>
  Result(const LWF::Pair<U, Bool> &base) : Base(base) {}
};

}}}} // namespace CShift::LWF::Collection::Associative

#endif // CSHIFT_LWF_COLLECTION_ASSOCIATIVE_CONTAINER_H
