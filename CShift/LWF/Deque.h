#ifndef CSHIFT_LWF_DEQUE_H
#define CSHIFT_LWF_DEQUE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Move/reference.h"
#include "LWF/Collection/Reversible/Deque/Low/Traits/Container.h"
#include "LWF/Collection/Reversible/Deque/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Deque {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  public:    typedef typename Base::Type      Type;
  public:    typedef typename Base::Allocator Allocator;
  public:    typedef typename Base::Iterator  Iterator;
  public:    typedef typename Base::Block     Block;
  protected: typedef typename Base::Capacity  Capacity;

  protected: Container(const Allocator &allocator) : Base(allocator) {}

  protected: Void ensureCapacity(UInt front, UInt back) {
    Capacity capacity(*this);
    if (front > capacity.front) enlarge(Base::mbegin(), front - capacity.front);
    if (back  > capacity.back ) enlarge(Base::mend  (), back  - capacity.back );
  }

  protected: Void setCapacity(UInt front, UInt back) {
    ensureCapacity(front, back);
    Capacity capacity(*this);
    if (front < capacity.front) shrink(Base::mrend (), capacity.front - front);
    if (back  < capacity.back ) shrink(Base::mrbegin(), capacity.back - back  );
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    typename Base::Shift shift(*this, first, last); UInt count = last - first;
    return (shift.front < shift.back) ?
              (Base::erase(last , Base::first(), count), last) :
              (Base::erase(first, Base::last (), count), first) ;
  }

  protected: template <typename RangeIterator>
  Iterator insert(Iterator position, RangeIterator first, RangeIterator last) {
    const UInt count = last - first;
    if (0 == count) { return position; }

    const typename Base::Distance distance(*this, position);

    if (distance.front < distance.back) {
      const UInt capacity = Base::frontCapacity();
      if (capacity < count) {
        const UInt expanse =
            Base::allocator().expanse(capacity, count, distance.size());
        enlarge(Base::mbegin(), (expanse + count) - capacity,
                position, first, last);
      }
      return Base::insertFront(position, first, last);
    } else {
      const UInt capacity = Base::backCapacity();
      if (capacity < count) {
        const UInt expanse =
          Base::allocator().expanse(capacity, count, distance.size());
        enlarge(Base::mend(), (count + expanse) - capacity,
                position, first, last);
      }
      return Base::insertBack(position, first, last);
    }
  }

  private:  struct Index {
    Index(const Container &container, const Iterator &iterator) :
      index(iterator - container.first()) {}
    Iterator operator () (const Container &container) const {
      return container.first() + index;
    } private: UInt index;
  };

  private: template <typename MapIterator>
  Void enlarge(const MapIterator &end, UInt count, Iterator &position) {
    Index index(*this, position);
    enlarge(end, count);
    position = index(*this);
  }

  private: template <typename MapIterator, typename RangeIterator>
  Void enlarge(const MapIterator &end, UInt count,
               Iterator &position, const RangeIterator &/*first*/, const RangeIterator &/*last*/,
               typename LWF::Traits::Prediction<!Base::template Is<RangeIterator>::Iterator>::Type * = 0) {
    enlarge(end, count, position);
  }

  private: template <typename MapIterator, typename RangeIterator>
  Void enlarge(const MapIterator &end, UInt count,
               Iterator &position, RangeIterator &first, RangeIterator &last,
               typename LWF::Traits::Prediction<Base::template Is<RangeIterator>::Iterator>::Type * = 0) {
    if (Base::contains(first)) {
      struct { Index first, last; } index = {
        Index(*this, first), Index(*this, last)
      }; enlarge(end, count, position);
      first = index.first(*this); last  = index.last(*this);
    } else {
      enlarge(end, count, position);
    }
  }  

  private: template <typename MapIterator>
  Void enlarge(MapIterator end, const typename Block::Enlarge::Spread &spread) {
    UInt count = spread.size();
    const Container &cthis = *this;
    for (typename Iterator::Index first = cthis.first().index(),
                                  last  = cthis.last ().index();
         count-- != 0;            this->first() = Base::at(first += end),
                                  this->last () = Base::at(last  += end)) {
      Block block(Base::allocator());
      end = Base::map.insert(end, block);
    }
  }

  private: template <typename MapIterator>
  Void shrink(MapIterator end, const typename Block::Shrink::Spread &spread) {
    UInt count = spread.size();
    const Container &cthis = *this;
    for (typename Iterator::Index first = cthis.first().index(),
                                  last  = cthis.last ().index();
         count-- != 0;            this->first() = Base::at(first -= end),
                                  this->last () = Base::at(last  -= end)) {
      end = Base::map.erase(end);
    }
  }
};

}} // namespace High::Traits

}}}}} // namespace CShift::LWF::Collection::Reversible::Deque


namespace CShift {
namespace LWF {

template <typename Type,
          typename Allocator = LWF::Collection::Reversible::Deque::Allocator<Type> >
struct Deque
  : LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::Reversible::Deque::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::Reversible::Array::Low ::Traits::Container<
    LWF::Collection::Reversible::Deque::Low ::Traits::Container<
    LWF::Collection::Traits::Container<Type, Allocator> > > > > > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::Reversible::Deque::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::Reversible::Array::Low ::Traits::Container<
    LWF::Collection::Reversible::Deque::Low ::Traits::Container<
    LWF::Collection::Traits::Container<Type, Allocator> > > > > > > > > Base;
  public:

  Deque(const Allocator &allocator = Allocator()) : Base(allocator) {}

  Deque(UInt count, const Type &value = Type(),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  Deque(const Iterator &first, const Iterator &last, const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  Deque(const Range &range,
        const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  Deque &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Deque(const LWF::Initializer::List<Type> &list,
        const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  Deque &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  Deque (const Deque &deque,
        const Allocator &allocator = Allocator())
    : Base(deque, allocator) {}

  Deque &operator = (const Deque &deque) {
    Base::operator = (deque);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Deque(Deque &&deque) : Base(LWF::Forward::reference<Base>(deque)) {}

  Deque &operator = (Deque &&deque) {
    Base::operator = (LWF::Forward::reference<Base>(deque));
    return *this;
  }
  #endif // C++11
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_DEQUE_H
