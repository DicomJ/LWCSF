#ifndef CSHIFT_LWF_VECTOR_H
#define CSHIFT_LWF_VECTOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Collection/Dynamic/Container.h"
#include "LWF/Collection/Reversible/Array/Container.h"
#include "LWF/Collection/Reversible/Vector/Low/Traits/Container.h"
#include "LWF/Collection/Container.h"
#include "LWF/Collection/Reversible/Vector/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
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

  protected: Void ensureCapacity(UInt front, UInt back) {
    Capacity capacity(*this);
    if (front > capacity.front || back > capacity.back)  {
      setCapacity(Capacity(LWF::max(capacity.front, front),
                           LWF::max(capacity.back , back )));
    }
  }
  protected: Void setCapacity(UInt front, UInt back) {
    Capacity capacity(*this);
    if (capacity.front != front || capacity.back != back) {
      setCapacity(Capacity(front, back));
    }
  }
  private: Void setCapacity(const Capacity &capacity) {
    const Base &cthis = *this;
    const UInt size = cthis.last() - cthis.first();
    Swapper base(capacity.size() + size, Base::allocator());
    base.first() = base.last() = base.begin() + capacity.front;
    Base::tail(base.last()).insert(cthis.first(), size);
    Base::swap(base);
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    typename Base::Shift shift(*this, first, last); UInt count = last - first;
    return (shift.front < shift.back) ?
              (Base::erase(last , Base::first(), count), last) :
              (Base::erase(first, Base::last (), count), first) ;
  }

  protected: template <typename RangeIterator>
  Iterator insert(const Iterator &position,
                  const RangeIterator &first, const RangeIterator &last) {
    const UInt count = last - first;
    if (0 == count) { return position; }

    Capacity capacity(*this);
    const typename Base::Distance distance(*this, position);

    if (distance.front < distance.back) {
      if (capacity.front < count) {
        capacity.front =
            Base::allocator().expanse(capacity.front, count, distance.size());
        return insert(capacity, distance, first, last);
      } else {
        return Base::insertFront(position, first, last);
      }
    } else {
      if (capacity.back < count) {
        capacity. back =
            Base::allocator().expanse(capacity. back, count, distance.size());
        return insert(capacity, distance, first, last);
      } else {
        return Base::insertBack(position, first, last);
      }
    }
  }
  private: template <typename RangeIterator>
  Iterator insert(const Capacity &capacity,
                  const typename Base::Distance &distance,
                  const RangeIterator &first, const RangeIterator &last) {
    const Container & cthis = *this;
    const UInt count = last - first;

    Swapper base(capacity.front
                + (distance.front + count + distance.back)
                  + capacity.back,
              Base::allocator());
    base.first() = base.last() = base.begin() + capacity.front;
    Base::tail(base.last()).
      insert(cthis.first(), distance.front).
      insert(first, count).
      insert(cthis.first() + distance.front, distance.back);
    Base::swap(base);
    return Base::last() - distance.back;
  }
};

}} // namespace High::Traits

}}}}} // namespace CShift::LWF::Collection::Reversible::Vector


namespace CShift {
namespace LWF {

template <typename Type,
          typename Allocator = LWF::Collection::Reversible::Vector::Allocator<Type> >
struct Vector
  : LWF::Collection::Dynamic::                         Container<
    LWF::Collection::Static::                          Container<
    LWF::Collection::Reversible::Array ::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array ::High::Traits::Container<
    LWF::Collection::Reversible::Vector::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array ::Low ::Traits::Container<
    LWF::Collection::Reversible::Array ::Low ::Traits::Container<
    LWF::Collection::Reversible::Vector::Low ::Traits::Container<
      Type, Allocator>  > > > > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                         Container<
    LWF::Collection::Static::                          Container<
    LWF::Collection::Reversible::Array ::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array ::High::Traits::Container<
    LWF::Collection::Reversible::Vector::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array ::Low ::Traits::Container<
    LWF::Collection::Reversible::Array ::Low ::Traits::Container<
    LWF::Collection::Reversible::Vector::Low ::Traits::Container<
      Type, Allocator>  > > > > > > > Base;
  public:

  Vector(const Allocator &allocator = Allocator()) : Base(allocator) {}

  Vector(UInt count, const Type &value = Type(),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  Vector(const Iterator &first, const Iterator &last,
         const Allocator &allocator = Allocator())
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

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VECTOR_H
