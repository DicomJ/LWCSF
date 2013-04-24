#ifndef CSHIFT_LWF_COLLECTION_DYNAMIC_FORWARD_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_DYNAMIC_FORWARD_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Initializer/List.h"
#include "LWF/Forward/reference.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Value/Ptr.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Dynamic {
namespace Forward {

template <typename Base>
struct Container : public Base {
  private: template <typename T> struct Is;
  public : typedef typename Base::Allocator  Allocator;
  public : typedef typename Base::Iterator   Iterator;
  public : typedef typename Iterator::Type   Type;

  UInt capacity() const { return Base::capacity(); }
  Void resize(UInt size, const Type &value = Type()) { Base::resize(size, value); }

  template <typename Iterator, typename Type>
  Iterator insert(const Iterator &iterator, const Type &value,
                  const typename LWF::Traits::Prediction<
                    !(Is<Type>::range ||  // insert(const Range &range)
                      Is<Type>::nonconst)  // insert(Unique::Ptr<U> )
                  >::Type & = typename LWF::Traits::Prediction<
                    !(Is<Type>::range || Is<Type>::nonconst)>::Type()) {
    return Base::template insert<LWF::Const::Value<Type> >(iterator, value);
  }
  template <typename Iterator>
  Iterator insert(const Iterator &iterator, Type &value) {
    return Base::template insert<LWF::Value<Type> >(iterator, value);
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  template <typename Iterator>
  Iterator insert(const Iterator &iterator, Type &&value) {
    return Base::template insert<LWF::Reference::Value<Type> >(iterator, value);
  }
  #endif // !C++11

  template <typename Iterator>
  Iterator insert(const Iterator &iterator, UInt count, const Type &value) {
    typedef typename LWF::Value<const Type>::template Ptr<Int> Ptr;
    return Base::insert(iterator, Ptr(&value), Ptr(&value, count));
  }

  template <typename Iterator, typename Range>
  Iterator insert(const Iterator &iterator, const Range &range,
                  typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) {
    return Base::insert(iterator, range.begin(), range.end());
  }
  template <typename Iterator, typename RangeIterator>
  Iterator insert(const Iterator &iterator,
                  const RangeIterator &first, const RangeIterator &last,
                  typename LWF::Traits::Prediction<!Is<RangeIterator>::count>::Type * = 0) {
    return Base::insert(iterator, first, last);
  }
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  template <typename Iterator>
  Iterator insert(const Iterator &iterator,
                  const LWF::Initializer::List<Type> &list) {
    return insert<Iterator, LWF::Initializer::List<Type> >(iterator, list);
  }
  #endif // C++11

  template <typename Iterator>
  Iterator erase(const Iterator &iterator,
                 typename LWF::Traits::Prediction<Is<Iterator>::Iterator>::Type * = 0) {
    return Base::erase(iterator);
  }
  template <typename Iterator>
  Iterator erase(const Iterator &first, const Iterator &last) {
    return Base::erase(first, last);
  }

  template <typename Range> typename Range::Iterator
  erase(const Range &range,
        typename LWF::Traits::Prediction<Is<Range>::range
                                      && !Is<Range>::Iterator>::Type * = 0) {
    return Base::erase(range.begin(), range.end());
  }

  template <typename Iterator>
  Void swap(const Iterator &one, const Iterator &other) {
    Base::swap(one, other);
  }

  Void swap(Container &container) {
    if (&container != this) { Base::swap(container); }
  }

  Void clear() { erase(Base::rbegin(), Base::rend()); }

  Void pushFront(UInt count, const Type &value) {
    insert(Base::rend(), count, value);
  }
  template <typename RangeIterator>
  Void pushFront(const RangeIterator &first, const RangeIterator &last) {
    insert(Base::rend(), first, last);
  }
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Void  pushFront(const LWF::Initializer::List<Type> &list) {
    insert(Base::rend(), list);
  }
  #endif // C++11
  template <typename Range>
  Void pushFront(const Range &range) { insert(Base::rend(), range); }
  Void popFront()                    { erase (Base::rend() - 1); }
  Void pushFront(      Type & value) { insert(Base::rend(), value); }
  Void pushFront(const Type & value) { insert(Base::rend(), value); }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Void pushFront(      Type &&value) { insert(Base::rend(),
                                              LWF::Forward::reference<Type>(value)); }
  #endif // !C++11

  Container &assign(      Type & value) { clear(); pushFront(value);  return *this; }
  Container &assign(const Type & value) { clear(); pushFront(value);  return *this; }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Container &assign(      Type &&value) {
    clear(); pushFront(LWF::Forward::reference<Type>(value));  return *this;}
  #endif // C++11
  Container &assign(UInt count, const Type &value) {
    clear(); pushFront(count, value); return *this;
  }

  template <typename RangeIterator>
  Container &assign(const RangeIterator &first, const RangeIterator &last,
                    typename LWF::Traits::Prediction<
                      !Is<RangeIterator>::count && Is<RangeIterator>::Iterator>::Type * = 0) {
    return assignBeforeClear(first, last);
  }
  template <typename RangeIterator>
  Container &assignBeforeClear(const RangeIterator &first,
                               const RangeIterator &last) {
    Iterator begin = insert<Iterator>(Base::rend(), first, last);
    erase(begin, Base::end());
    return *this;
  }
  template <typename RangeIterator>
  Container &assign(const RangeIterator &first, const RangeIterator &last,
                    typename LWF::Traits::Prediction<
                      !Is<RangeIterator>::count && !Is<RangeIterator>::Iterator>::Type * = 0) {
    clear(); pushFront(first, last);
    return *this;
  }
  template <typename Range>
  Container &assign(const Range &range,
                    typename LWF::Traits::Prediction<Is<Range>::range && Is<Range>::container>::Type * = 0) {
    if (this != &range) {
      clear(); pushFront(range.begin(), range.end());
    }
    return *this;
  }
  template <typename Range>
  Container &assign(const Range &range,
                    typename LWF::Traits::Prediction<Is<Range>::range && !Is<Range>::container>::Type * = 0) {
    return assign(range.begin(), range.end());
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Container &assign(const LWF::Initializer::List<Type> &list) {
    clear(); return assign<LWF::Initializer::List<Type> >(list);
  }
  #endif // C++11

  ~Container() { clear(); }

  Container(const Allocator &allocator) : Base(allocator) {}

  Container(UInt count, const Type &value,
            const Allocator &allocator) : Base(allocator) {
    insert(Base::rend(), count, value);
  }

  template <typename RangeIterator>
  Container(const RangeIterator &first, const RangeIterator &last,
            const Allocator &allocator) : Base(allocator) {
    insert(Base::rend(), first, last);
  }

  template <typename Range>
  Container(const Range &range,
            const Allocator &allocator) : Base(allocator) {
    Container::insert(Base::rend(), range);
  }

  template <typename Range>
  Container &operator = (const Range &range) { return assign(range);  }

  Container(const Container &container) : Base(container) {}
  Container &operator = (const Container &container) { Base::operator = (container); return *this; }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)) {}

  Container &operator = (Container &&container) {
    if (this != &container) {
      clear();
      Base::operator = (LWF::Forward::reference<Base>(container));
    }
    return *this;
  }
  #endif // C++11
};

template <typename Base>
template <typename T>
struct Container<Base>::Is {
  static const Bool count =
      LWF::Type<typename LWF::Type<T>::Kind>::Is::
          Equal::template To<typename LWF::Type<UInt>::Kind>::type;
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Iterator>::type;
  static const Bool nonconst =
      LWF::Type<T>::Is::nonconst;
  static const Bool container =
      LWF::Type<Container>::Is::Base::template Of<T>::type;
  static const Bool range =
      LWF::Type<T>::Is::range;
};

}}}}} // namespace CShift::LWF::Collection::Dynamic::Forward

#endif // CSHIFT_LWF_COLLECTION_DYNAMIC_FORWARD_CONTAINER_H
