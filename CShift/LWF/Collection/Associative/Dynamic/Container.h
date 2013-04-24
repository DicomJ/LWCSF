#ifndef CSHIFT_LWF_COLLECTION_ASSOCIATIVE_DYNAMIC_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_ASSOCIATIVE_DYNAMIC_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Initializer/List.h"
#include "LWF/Forward/reference.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Range.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Associative {
namespace Dynamic {

namespace Traits {

template <typename Traits, Bool = Traits::multi>
struct Container : Container<Traits, False> {

  private: typedef Container<Traits, False> Base;
  public : typedef typename Base::Key Key;
  public : typedef typename Base::Comparer Comparer;
  public : typedef typename Base::Allocator Allocator;
  public : typedef typename Base::Iterator Iterator;
  public : typedef typename Base::Type Type;

  template <typename RangeIterator>
  Void insert(RangeIterator begin, const RangeIterator &end) {
    Base::insert(begin, end);
  }
  template <typename Range>
  Void insert(const Range &range,
              typename LWF::Traits::Prediction<
                            !Base::template Is<Range>::Type>::Type * = 0) {
    return Base::insert(range);
  }
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Void insert(const LWF::Initializer::List<Type> &list) {
    Base::template insert<LWF::Initializer::List<Type> >(list);
  }
  #endif // C++11

  Iterator insert(const Type &value) {
    return Base::insert(value).iterator();
  }
  Iterator insert(Type &value) {
    return Base::insert(value).iterator();
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Iterator insert(Type &&value) {
    return Base::insert(LWF::Forward::reference<Type>(value));
  }
  #endif // C++11

  template <typename Iterator>
  Iterator insert(const Iterator &iterator, const Type &value) {
    return Base::insert(iterator, value).iterator();
  }
  template <typename Iterator>
  Iterator insert(const Iterator &iterator, Type &value) {
    return Base::insert(iterator, value).iterator();
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  template <typename Iterator>
  Iterator insert(const Iterator &iterator, Type &&value) {
    return Base::insert(iterator, LWF::Forward::reference<Type>(value)).iterator();
  }
  #endif // C++11

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}
};

template <typename Base>
struct Container<Base, False> : Base {

  protected: template <typename T> struct Is;
  public   : typedef typename Base::Type Type;
  public   : typedef typename Base::Comparer Comparer;
  public   : typedef typename Base::Allocator Allocator;
  public   : typedef typename Base::Iterator Iterator;
  public   : typedef typename Base::Key Key;

  const Container &Unique() const { return *this; }
        Container &Unique()       { return *this; }

  template <typename RangeIterator>
  Void insert(RangeIterator begin, const RangeIterator &end) {
    for (; begin != end; ++begin) { insert(*begin); }
  }
  template <typename Range>
  Void insert(const Range &range,
              typename LWF::Traits::Prediction<!Is<Range>::Type>::Type * = 0) {
    return insert(range.begin(), range.end());
  }
  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Void insert(const LWF::Initializer::List<Type> &list) {
    insert<LWF::Initializer::List<Type> >(list);
  }
  #endif // C++11

  typename Base::Insert::template Result<Iterator>
  insert(const Type &value) {
    return insert(Base::end(), value);
  }
  typename Base::Insert::template Result<Iterator>
  insert(Type &value) {
    return insert(Base::end(), value);
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  typename Base::Insert::template Result<Iterator>
  insert(Type &&value) {
    return insert(Base::end(),  LWF::Forward::reference<Type>(value));
  }
  #endif // C++11

  template <typename Iterator>
  typename Base::Insert::template Result<Iterator>
  insert(const Iterator &iterator, const Type &value) {
    return insert_(iterator, value);
  }
  template <typename Iterator>
  typename Base::Insert::template Result<Iterator>
  insert(const Iterator &iterator, Type &value) {
    return insert_(iterator, value);
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  template <typename Iterator>
  typename Base::Insert::template Result<Iterator>
  insert(const Iterator &iterator, Type &&value) {
    return insert_(iterator, LWF::Forward::reference<Type>(value));
  }
  #endif // C++11

  UInt erase(const Key &key) { return Base::erase(key); }

  Void erase(const Iterator &iterator) {
    Base::erase(iterator);
  }
  Void erase(const typename Base::Reverse::Iterator &iterator) {
    Base::erase(iterator + 1);
  }
  Void erase(Iterator first, const Iterator &last) {
    if (LWF::range(*this) == LWF::range(first, last)) Base::clear();
    else while (first != last) { Base::erase(first++); }
  }
  Void erase(const typename Base::Reverse::Iterator &first,
             const typename Base::Reverse::Iterator &last) {
    erase(Iterator(last), Iterator(first));
  }

  template <typename Range>
  Void erase(const Range &range,
              typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) {
    erase(range.begin(), range.end());
  }

  Iterator find(const Key &key) { return Base::find(key); }
  typename Base::Const::Iterator find(const Key &key) const {
    return Base::find(key);
  }

  LWF::Range<Iterator> equalRange(const Key &key) {
    return Base::equalRange(key);
  }
  LWF::Range<typename Base::Const::Iterator> equalRange(const Key &key) const {
    return Base::equalRange(key);
  }

  Void clear() { Base::clear(); }

  Void swap(Container &container) {
    if (this != &container) {
      Base::swap(container);
    }
  }

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}
  public: ~Container() { clear(); }

  private: typename Base::Insert::template Result<Iterator >
  insert_(const Iterator &iterator, const Type &value) {
    return Base::template insert<LWF::Const::Value<Type> >(iterator, value);
  }
  private: typename Base::Insert::template Result<Iterator >
  insert_(const Iterator &iterator, Type &value) {
    return Base::template insert<LWF::Value<Type> >(iterator, value);
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  private: typename Base::Insert::template Result<Iterator >
  insert_(const Iterator &iterator, Type &&value) {
    return Base::template insert<LWF::Reference::Value<Type> >(iterator, value);
  }
  #endif // C++11
};

template <typename Base>
template <typename T>
struct Container<Base, False>::Is {
  static const Bool Type =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Type>::type;
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Iterator>::type;
  static const Bool range =
      LWF::Type<T>::Is::range;
};

} // namespace Tratis

template <typename Traits>
struct Container
  : LWF::Collection::Associative::Dynamic::Traits::Container<Traits>
{
  private: typedef
    LWF::Collection::Associative::Dynamic::Traits::Container<Traits> Base;
  public:

  typedef typename Base::Type Type;
  typedef typename Base::Comparer Comparer;
  typedef typename Base::Allocator Allocator;
  typedef typename Base::Iterator Iterator;
  typedef typename Base::Key Key;

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Container(const LWF::Initializer::List<Type> &list,
            const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) { Base::insert(list); }

  Container &operator = (const LWF::Initializer::List<Type> &list) {
    Base::clear(); Base::insert(list); return *this;
  }
  #endif // C++11

  Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}

  template <typename Range>
  Container(const Range &range,
            const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) { Base::insert(range); }

  template <typename RangeIterator>
  Container(RangeIterator begin, const RangeIterator &end,
            const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) { Base::insert(begin, end); }

  Container(const Container &container,
            const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) { insert(container); }
  Container &operator = (const Container &container) {
    if (&container != this) { Base::clear(); Base::insert(container); } return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)) {}

  Container &operator = (Container &&container) {
    if (this != &container) {
      Base::clear(); Base::operator = (LWF::Forward::reference<Base>(container));
    } return *this;
  }
  #endif // C++11
};

}}}}} // namespace CShift::LWF::Collection::Associative::Dynamic

#endif // CSHIFT_LWF_COLLECTION_ASSOCIATIVE_DYNAMIC_CONTAINER_H
