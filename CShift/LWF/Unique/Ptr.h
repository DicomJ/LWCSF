#ifndef CSHIFT_LWF_UNIQUE_PTR_H
#define CSHIFT_LWF_UNIQUE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Traits/Weakless/Ptr.h"
#include "LWF/Traits/Nonconst.h"
#include "LWF/Deleter.h"
#include "LWF/Std/Allocator.h"
#include "LWF/Algorithm/swap.h"


namespace CShift {
namespace LWF {
namespace Unique {

namespace Traits {

template <typename Base_, typename Deleter_>
struct Ptr : Base_, private Deleter_ {

  private: typedef Base_ Base;
  public : typedef typename Base::Type Type;
  public : typedef         Deleter_ Deleter;

  Ptr(Type *ptr, const Deleter &deleter = Deleter())
    : Base(ptr), Deleter(deleter) {}

  Ptr(Ptr &ptr)
    : Base(static_cast<Base &>(ptr)), Deleter(static_cast<Deleter &>(ptr)) {
    ptr.Weak() = null;
  }

  Ptr &operator = (Ptr &ptr) {
    if (this != &ptr) {
      *this = null;
      Base::operator = (static_cast<Base &>(ptr));
      Deleter::operator = (static_cast<Deleter &>(ptr));
      ptr.Weak() = null;
    }
    return *this;
  }

  Ptr(const Null &ptr, const Deleter& deleter) : Base(ptr), Deleter(deleter) {}

  Ptr &operator = (const Null &) {
    if (*this != null) { Deleter::Delete(&**this); }
    Weak() = null;
    return *this;
  }

  ~Ptr() { *this = null; }

  Base& Weak() { return *this; }
  Base Weak() const { return *this; }

  Void swap(Ptr &ptr) { LWF::swap<Base>(*this, ptr); }

  template <typename U, typename D>
  operator Ptr<U, D> &() {

    LWF::Traits::Lame(static_cast<const typename U::Caster &>(
                        static_cast<const Base &>(*this)));

    LWF::Type<typename Deleter::Unbiased::Type *>().cast(
          LWF::Type<typename D::Unbiased::Type *>());

    return *(Ptr<U, D> *)this;
  }

  typedef Ptr Caster;

        Deleter& owner()       { return *this; }
  const Deleter& owner() const { return *this; }
  //private: Deleter deleter;
};

} // namespace Traits

template <typename Traits>
struct Deleter : LWF::Deleter<Traits> { };

template <typename Traits>
struct Allocator : LWF::Std::Allocator, LWF::Unique::Deleter<Traits> { };

template <typename Traits,
          typename Deleter = LWF::Unique::Deleter<Traits> >
struct Ptr
  : LWF::Ptr<LWF::Unique::Traits::Ptr<
    LWF::Traits::Weakless::Ptr<Weak::Ptr<Traits> >,
    Deleter> >
{
  private: typedef
    LWF::Ptr<LWF::Unique::Traits::Ptr<
    LWF::Traits::Weakless::Ptr<Weak::Ptr<Traits> >,
    Deleter> > Base;
  public: typedef
    typename Base::Type Type;

  Ptr(Type *ptr, const Deleter &deleter = Deleter()) : Base(ptr, deleter) {}

  Ptr(const Null &ptr = null, const Deleter& deleter = Deleter()) : Base(ptr, deleter) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (Ptr &ptr) { Base::operator = (ptr); return *this; }

#if PLATFORM_COMPILER_RVALUE_REFERENCE
  Ptr(Ptr &&ptr) : Base(ptr) {}
  Ptr &operator = (Ptr &&ptr) { Base::operator = (ptr); return *this; }
#else // !C++11
  private: typedef LWF::Traits::Nonconst<Base> Nonconst;
  public: friend class LWF::Traits::Mutable::Type<Ptr>;
  operator Nonconst () { return Nonconst(*this); }
  Ptr(Nonconst ptr) : Base(ptr) {}
  Ptr &operator = (Nonconst ptr) { Base::operator = (ptr); return *this; }
#endif // !C++11

  template <typename U, typename D>
  operator Ptr<U, D> &() {
    LWF::Traits::Lame(static_cast<typename Ptr<U, D>::Caster &>(static_cast<Base &>(*this)));
    return *(Ptr<U, D> *)this;
  }
};

}}} // namespace CShift::LWF::Unique

#endif // CSHIFT_LWF_UNIQUE_PTR_H
