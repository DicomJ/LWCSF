#ifndef CSHIFT_LWF_RING_VECTOR_H
#define CSHIFT_LWF_RING_VECTOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Ring/Ptr.h"
#include "LWF/Collection/Dynamic/Container.h"
#include "LWF/Collection/Ring/Array/Container.h"
#include "LWF/Collection/Reversible/Vector/Low/Traits/Container.h"
#include "LWF/Collection/Reversible/Vector/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Ring {
namespace Vector {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  public:    typedef typename Base::Allocator  Allocator;
  public:    typedef typename Base::Iterator   Iterator;
  protected: typedef typename Base::Capacity   Capacity;
  private:   typedef typename Base::template Swapper<Container> Swapper;

  protected: ConstructionTransparency(Container, Base) {}

  protected: Void ensureCapacity(UInt capacity) {
    if (Capacity(*this).size() < capacity) { setCapacity(capacity); }
  }
  protected: Void setCapacity(UInt capacity) {
    const Base &cthis = *this;
    const UInt size = cthis.last() - cthis.first();
    Swapper base(size + capacity, Base::allocator());
    Base::tail(base.last()).insert(cthis.first(), size);
    Base::swap(base);
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    typename Base::Shift shift(*this, first, last); UInt count = last - first;
    return (shift.front < shift.back) ?
              (Base::erase(last , Base::first(), count), last ):
              (Base::erase(first, Base::last (), count), first);
  }

  protected: template <typename RangeIterator>
  Iterator insert(const Iterator &position,
                  const RangeIterator &first, const RangeIterator &last) {
    const UInt count = last - first;
    if (0 == count) { return position; }

    const typename Base::Distance distance(*this, position);
    UInt capacity = Capacity(*this).size();
    if (capacity < count) {
      capacity = Base::allocator().expanse(capacity, count, distance.size());
      return insert(capacity, distance, first, last);
    } else {
      if (distance.front < distance.back) {
        return Base::insertFront(position, first, last);
      } else {
        return Base::insertBack(position, first, last);
      }
    }
  }

  private: template <typename RangeIterator>
  Iterator insert(UInt capacity,
                  const typename Base::Distance &distance,
                  const RangeIterator &first, const RangeIterator &last) {
    const Container & cthis = *this;
    const UInt count = last - first;

    Swapper base((distance.front + count + distance.back) + capacity,
              Base::allocator());
    base.first() = base.last() = base.begin() + capacity / 2;
    Base::tail(base.last()).
      insert(cthis.first(), distance.front).
      insert(first, count).
      insert(cthis.first() + distance.front, distance.back);
    Base::swap(base);
    return Base::last() - distance.back;
  }
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef Base Reversible;
  struct Iterator;

  Iterator begin() const {
    return Iterator(Base::begin(), Base::begin(), Base::end());
  }
  Void end() const; // = delete

  ConstructionTransparency(Container, Base) {}
};

template <typename CBase>
struct Container<CBase>::Iterator : LWF::Ring::Ptr<typename CBase::Iterator> {
  private: typedef LWF::Ring::Ptr<typename CBase::Iterator> Base; public:

  Iterator(const typename CBase::Iterator &base,
           const typename CBase::Iterator &begin,
           const typename CBase::Iterator &end)
     : Base(base, begin, end - begin){}

  Iterator(const Null & = null) : Base(null) {}
  Iterator &operator = (const Null &) { Base::operator = (null); return *this; }

  Iterator(const Iterator &iterator) : Base(static_cast<const Base &>(iterator)) {}
  Iterator &operator = (const Iterator &iterator) {
    Base::operator = (static_cast<const Base &>(iterator)); return *this;
  }

  WeaknessTransparency(Iterator, Base) {}
};

}} // namespace Low::Traits

template <typename Type>
struct Allocator : LWF::Collection::Reversible::Vector::Allocator<Type> {};

}}}}} // namespace CShift::LWF::Collection::Ring::Vector


namespace CShift {
namespace LWF {
namespace Ring {

template <typename Type,
          typename Allocator = LWF::Collection::Ring::Vector::Allocator<Type> >
struct Vector
  : LWF::Collection::Dynamic::                         Container<
    LWF::Collection::Static::                          Container<
    LWF::Collection::Ring::      Array ::High::Traits::Container<
    LWF::Collection::Dynamic::   Array ::High::Traits::Container<
    LWF::Collection::Ring::      Vector::High::Traits::Container<
    LWF::Collection::Dynamic::   Array ::Low ::Traits::Container<
    LWF::Collection::Ring::      Array ::Low ::Traits::Container<
    LWF::Collection::Ring::      Vector::Low ::Traits::Container<
    LWF::Collection::Reversible::Vector::Low ::Traits::Container<
                             Type, Allocator> > > > > > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                         Container<
    LWF::Collection::Static::                          Container<
    LWF::Collection::Ring::      Array ::High::Traits::Container<
    LWF::Collection::Dynamic::   Array ::High::Traits::Container<
    LWF::Collection::Ring::      Vector::High::Traits::Container<
    LWF::Collection::Dynamic::   Array ::Low ::Traits::Container<
    LWF::Collection::Ring::      Array ::Low ::Traits::Container<
    LWF::Collection::Ring::      Vector::Low ::Traits::Container<
    LWF::Collection::Reversible::Vector::Low ::Traits::Container<
                             Type, Allocator> > > > > > > > > Base;
  public:

  Vector(const Allocator &allocator = Allocator()) : Base(allocator) {}

  Vector(UInt count, const Type &value = Type(),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  Vector(const Iterator &first, const Iterator &last, const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  Vector(const Range &range,
         const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  Vector &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Vector(const LWF::Initializer::List<Type> &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  Vector &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  Vector (const Vector &vector,
          const Allocator &allocator = Allocator())
    : Base(vector, allocator) {}

  Vector &operator = (const Vector &vector) {
    Base::operator = (vector);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Vector(Vector &&vector) : Base(LWF::Forward::reference<Base>(vector)) {}

  Vector &operator = (Vector &&vector) {
    Base::operator = (LWF::Forward::reference<Base>(vector));
    return *this;
  }
  #endif // C++11
};

}}} // namespace CShift::LWF::Ring

#endif // CSHIFT_LWF_RING_VECTOR_H
