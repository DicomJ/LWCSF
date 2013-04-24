#ifndef CSHIFT_LWF_COLLECTION_DYNAMIC_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_DYNAMIC_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Range.h"
#include "LWF/Value/Ptr.h"
#include "LWF/Collection/Dynamic/Forward/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Dynamic {

namespace Traits {

template <typename Base>
struct Container : Base {
  typedef typename Base::Iterator   Iterator;
  typedef typename Iterator::Type   Type;

  template <typename Type>
  Iterator insert(const Iterator &iterator, const Type &value) {
    return Base::insert(iterator, value);
  }

  template <typename Type> typename Base::Reverse::Iterator
  insert(const typename Base::Reverse::Iterator &iterator, const Type &value) {
    return Base::insert(iterator, value) - 1;
  }

  template <typename RangeIterator>
  Iterator insert(const Iterator &iterator,
                  const RangeIterator &first, const RangeIterator &last) {
    return Base::insert(iterator, first, last);
  }
  template <typename RangeIterator> typename Base::Reverse::Iterator
  insert(const typename Base::Reverse::Iterator &iterator,
         const RangeIterator &first, const RangeIterator &last) {
    UInt size = (last - first);
    return Base::insert(iterator, first, last) - size;
  }

  Iterator erase(const Iterator &iterator) {
    return Base::erase(iterator);
  }
  typename Base::Reverse::Iterator
  erase(const typename Base::Reverse::Iterator &iterator) {
    return Base::erase(iterator + 1);
  }

  Iterator erase(const Iterator &first, const Iterator &last) {
   return Base::erase(first, last);
  }
  typename Base::Reverse::Iterator
  erase(const typename Base::Reverse::Iterator &first,
        const typename Base::Reverse::Iterator &last) {
    return Base::erase(last, first);
  }
  Void swap(const Iterator &one, const Iterator &other) {
    return Base::swap(one, other);
  }
  Void swap(const typename Base::Reverse::Iterator &one,
                     const typename Base::Reverse::Iterator &other) {
    return Base::swap(one + 1, other + 1);
  }
  Void swap(Container &container) { Base::swap(container); }

  ConstructionTransparency(Container, Base) {}
};

} // namespace Traits

template <typename Traits>
struct Container
  : LWF::Collection::Dynamic::Forward::Container<
    LWF::Collection::Dynamic::Traits::Container<Traits> > {
  private: typedef
    LWF::Collection::Dynamic::Forward::Container<
    LWF::Collection::Dynamic::Traits::Container<Traits> > Base;
  public:

  typedef typename Base::Iterator   Iterator;
  typedef typename Iterator::Type   Type;

  #if PLATFORM_COMPILER_RVALUE_REFERENCE

  Void pushBack (      Type &&value) { Base::insert(Base::rbegin(),
                                              LWF::Forward::reference<Type>(value)); }
  #endif // !C++11
  Void pushBack(       Type &value) { Base::insert(Base::rbegin(), value); }
  Void pushBack(const  Type &value) { Base::insert(Base::rbegin(), value); }
  Void popBack()                    { Base::erase (Base::rbegin()); }
  template <typename Range>
  Void pushBack(const Range &range) { Base::insert(Base::rbegin(), range); }
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Void pushBack(const LWF::Initializer::List<Type> &list) {
    Base::insert(Base::rbegin(), list);
  }
  #endif // C++11
  template <typename RangeIterator>
  Void pushBack(const RangeIterator &first, const RangeIterator &last) {
    Base::insert(Base::rbegin(), first, last);
  }
  Void pushBack(UInt count, const Type &value) {
    Base::insert(Base::rbegin(), count, value);
  }

  ConstructionTransparency(Container, Base) {}
};

}}}} // namespace CShift::LWF::Collection::Dynamic

#endif // CSHIFT_LWF_COLLECTION_DYNAMIC_CONTAINER_H
