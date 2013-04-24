#ifndef CSHIFT_LWF_RANGE_H
#define CSHIFT_LWF_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Algorithm/min.max.h"
#include "LWF/OutOfRange/Exception.h"

namespace CShift {
namespace LWF {

namespace Traits {

template <typename Traits>
struct Range {

  typedef typename LWF::Weak::Cast<Traits>::Range::Ptr Iterator;

  template <typename Another>
  Range(const Another &range)
    : begin_(range.begin()), end_(range.end()) {}

  Range(const Iterator &begin, const Iterator &end)
     : begin_(begin), end_(end) {}

  Range(const Iterator &begin, Int size)
     : begin_(begin), end_(begin + size) {}

  Iterator begin() const { return begin_; }
  Iterator end  () const { return end_  ; }

  protected: Iterator begin_, end_;
};

} // namespace Traits

template <typename Traits>
struct Range
  : LWF::Collection::Static::Container<LWF::Traits::Range<Traits> >
{
  private: typedef
    LWF::Collection::Static::Container<LWF::Traits::Range<Traits> > Base;
  public:

  typedef typename Base::Iterator Iterator;
  typedef typename Base::Type     Type;

  ConstructionTransparency(Range, Base) {}

  typename Base::Const::Iterator position(UInt pos) const {
    if (pos > Base::size()) { LWF::Exception::Throw(LWF::OutOfRange::Exception()); }
    return Base::begin() + pos;
  }
  Range<typename Base::Const::Iterator>
  range(UInt pos, UInt count) const {
    typename Base::Const::Iterator begin = position(pos);
    return Range<typename Base::Const::Iterator>(
                  begin, begin + LWF::min(Base::size() - pos, count));
  }

  Range operator + (Int count) const {
    return Range(Base::begin() + count, Base::end() + count);
  }
  Range operator - (Int count) const { return *this + -count; }

  Bool operator == (const Range &range) const {
    return this->begin() == range.begin() && this->end() == range.end() ;
  }
  Bool operator != (const Range &range) const { return !(*this == range); }

  template <typename AnyIterator>
  Bool equal(AnyIterator source) const;

  Bool equal(const Type &value) const {
    return till(typename Range::Condition::template
                          Equal<Type>(value)) == Base::end();
  }

  Void reverse() {
    Iterator first = Base::begin();
    typename Base::Reverse::Iterator rfirst = Base::rbegin();

    for (; typename Base::Reverse::Iterator(first) - rfirst > 1; ++first, ++rfirst) {
      LWF::swap(*first, *rfirst);
    }
  }

  template <typename Operation>
  Iterator forEach(Operation operation) const {
    Iterator iterator = Base::begin();
    for (;iterator != Base::end(); ++iterator) { operation(*iterator);
    } return iterator;
  }

  template <typename Condition>
  Iterator till(Condition condition) const {
    Iterator iterator = Base::begin();
    for (; iterator != Base::end(); ++iterator) {
      if (!condition(*iterator)) { break ; }
    } return iterator;
  }

  template <typename Condition>
  Iterator tillNot(Condition condition) const {
    return till(typename Range::Condition::template Not<Condition>(condition));
  }

  Bool contains(const Iterator &iterator) const {
    return Base::begin() <= iterator && iterator < Base::end();
  }

  Bool contains(const Type &value) const {
    return find(value) != Base::end();
  }

  template <typename AnyIterator>
  Iterator fill(const AnyIterator &iterator,
                typename LWF::Traits::Prediction<
                  !LWF::Type<AnyIterator>::Is::Equal::template To<Iterator>::type
                  >::Type * = 0) {
    return forEach(typename Range::Operator::Fill::With::template
                   Iterator<AnyIterator>(iterator));
  }

  Iterator fill(const Iterator &iterator) {
    if (Base::begin() == iterator) { return Base::end(); }
    else {
      return forEach(typename Range::Operator::Fill::With::template
                     Iterator<Iterator>(iterator));
    }
  }

  Iterator fill(const Type &value) {
    return forEach(typename Range::Operator::Fill::With::Value(value));
  }

  Iterator find(const Type &value) const {
    return find(typename Range::Condition::template Equal<Type>(value));
  }

  template <typename What>
  Iterator find(What what) const { return tillNot(what); }

  template <typename How, typename What>
  Iterator search(const How &how, const What &range) const {
    return how(*this, range);
  }

  struct Condition {

    template <typename Type>
    struct Equal {
      Bool operator() (const Type &value_) { return value == value_; }
      Equal(const Type &value_) : value(value_) {}
      private: const Type &value;
    };

    template <typename AnotherCondition> struct Not {
      Bool operator() (const Type &value) { return !condition(value); }
      Not(AnotherCondition anotherCondition) : condition(anotherCondition) {}
      private: AnotherCondition condition;
    };
  };

  struct Operator {
  struct Fill {
  struct With {
    template <typename AnyIterator>
    struct Iterator {
      Iterator(const AnyIterator &iterator_) : iterator(iterator_) {}
      Void operator()(Type &value) { value = *iterator; ++iterator; }
      private: AnyIterator iterator;
    };
    struct Value {
      Value(const Type &value_) : value(value_) {}
      Void operator()(Type &value) { value = this->value; }
      private: const Type &value;
    };
  };};}; // Operator::Fill::With
};

template <typename Traits>
template <typename AnyIterator>
Bool Range<Traits>::equal(AnyIterator source) const {
  for (Iterator iterator = Base::begin(); iterator != Base::end();
       ++iterator, ++source) {
    if (*iterator != *source) return False;
  }
  return True;
}


template <typename Iterator>
LWF::Range<Iterator> range(const Iterator &begin,
                           const Iterator &end) {
  return LWF::Range<Iterator>(begin, end);
}

template <typename Iterator>
LWF::Range<Iterator> range(const Iterator &begin, Int size) {
  return LWF::Range<Iterator>(begin, size);
}

template <typename Another>
LWF::Range<typename Another::Const::Iterator> range(const Another &range) {
  return LWF::range(range.begin(), range.end());
}

template <typename Another>
LWF::Range<typename Another::Iterator> range(Another &range) {
  return LWF::range(range.begin(), range.end());
}

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_RANGE_H

