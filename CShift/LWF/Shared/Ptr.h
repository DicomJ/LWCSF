#ifndef CSHIFT_LWF_SHARED_PTR_H
#define CSHIFT_LWF_SHARED_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Move/reference.h"
#include "LWF/Custom/Allocator.h"
#include "LWF/Destroying/Deleter.h"


namespace CShift {
namespace LWF {
namespace Shared {

namespace Traits {

template <typename Counter, typename Owner_, typename Deallocator_>
struct Dynamic {
  typedef Owner_ Owner;
  typedef Deallocator_ Deallocator;
  typedef LWF::Destroying::Deleter<Dynamic, Deallocator> Deleter;

  Dynamic(const Owner &owner_, const Deallocator &deallocator_)
    : counter(1), owner(owner_), deallocator(deallocator_) { }

  Counter counter; Owner owner; Deallocator deallocator;
};

template <typename Base_, typename Dynamic>
struct Ptr : Base_ {
  private: typedef Base_ Base; public:

  Ptr(const Null &ptr, const Dynamic &dynamic_) : Base(ptr), dynamic(dynamic_) {}
  Ptr(const Base &ptr, const Dynamic &dynamic_) : Base(ptr), dynamic(dynamic_) {}

  Ptr(const Ptr &ptr)
    : Base(static_cast<const Base &>(ptr)), dynamic(ptr.dynamic) {
    if (dynamic != null) { ++dynamic->counter; }
  }

  Ptr &operator = (const Ptr &ptr) {
    if (this != &ptr) {
      *this = null;
      Base::operator = (static_cast<const Base &>(ptr));
      dynamic = ptr.dynamic;
      if (dynamic != null) { ++dynamic->counter; }
    }  return *this;
  }

  Ptr &operator = (const Null &) {
  if (dynamic != null
      && 0 == --dynamic->counter) {
      LWF::Unique::Ptr<typename Base::Type,
                       typename Dynamic::Type::Owner>(&**this, dynamic->owner);
      LWF::Unique::Ptr<typename Dynamic::Type,
                       typename Dynamic::Type::Deleter>(&*dynamic, dynamic->deallocator);
    }
    Base::operator = (null);
    dynamic = null;
    return *this;
  }

  ~Ptr() { *this = null; }

  typename Dynamic::Type::Owner owner() const { return dynamic->owner; }

  struct Release : Base_ {
    private: typedef Base_ Base; public:
    Release(Ptr &ptr_) : Base(static_cast<const Base &>(ptr_)), ptr(ptr_) {}
    Release operator = (const Null &) {
      Base::operator = (null);
      ptr.Base::operator = (null);
      ptr = (null);
      return *this;
    } Ptr &ptr;
  };

  Release Weak() { return *this; }
  Base Weak() const { return *this; }

  Bool unique() const { return dynamic->counter == 1; }

  Void swap(Ptr &ptr) {
    LWF::swap<Base>(*this, ptr);
    LWF::swap<Dynamic>(dynamic, ptr.dynamic);
  }

  template <typename U, typename D>
  operator const Ptr<U, D> &() const {
    LWF::Traits::Lame(static_cast<const typename U::Caster &>(
                      static_cast<const Base &>(*this)));
    //LWF::Traits::Lame(static_cast<const D &>(dynamic));
    return *(const Ptr<U, D> *)this;
  }

  private: Dynamic dynamic;
};

} // namespace Traits

namespace Counter {

template <typename Counter>
struct Allocator : LWF::Std::Allocator {};

} // namespace Counter

template <typename Traits,
          typename Deleter = LWF::Unique::Deleter<Traits>,
          typename Counter = UInt,
          typename DynamicAllocator = LWF::Shared::Counter::Allocator<Counter>,
          typename Dynamic = LWF::Shared::Traits::Dynamic<Counter, Deleter, DynamicAllocator> >
struct Ptr
  : LWF::Ptr<LWF::Shared::Traits::Ptr<
    LWF::Traits::Weakless::Ptr<Weak::Ptr<Traits> >, Weak::Ptr<Dynamic> > >
{
  private: typedef
    LWF::Ptr<LWF::Shared::Traits::Ptr<
    LWF::Traits::Weakless::Ptr<Weak::Ptr<Traits> >, Weak::Ptr<Dynamic> > > Base;
  public: typedef
    typename Base::Type Type;

  Ptr(Type *ptr,
      const Deleter &deleter = Deleter(),
      const DynamicAllocator &dynamicAllocator = DynamicAllocator())
    : Base(ptr, new (dynamicAllocator) Dynamic(deleter, dynamicAllocator)) {}

  Ptr(const Null &ptr = null,
      const Deleter &deleter = Deleter(),
      const DynamicAllocator &dynamicAllocator = DynamicAllocator())
    : Base(ptr, new (dynamicAllocator) Dynamic(deleter, dynamicAllocator)) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U, typename D, typename C, typename CA>
  Ptr(const Ptr<U, D, C, CA> &ptr) : Base(ptr) {}

  template <typename U, typename D, typename C, typename CA>
  Ptr &operator = (const Ptr<U, D, C, CA> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }
};

}}} // namespace CShift::LWF::Shared

#endif // CSHIFT_LWF_SHARED_PTR_H
