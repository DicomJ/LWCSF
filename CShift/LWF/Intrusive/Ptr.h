#ifndef CSHIFT_LWF_INTRUSIVE_PTR_H
#define CSHIFT_LWF_INTRUSIVE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Traits/Weakless/Ptr.h"


namespace CShift {
namespace LWF {
namespace Intrusive {

namespace Traits {

template <typename Traits, typename Base_>
struct Ptr : Base_ {
  private: typedef Base_ Base;
  public : typedef Traits Type;
  struct Return {
    typedef typename LWF::Traits::Uvalue::Ptr<Base, typename Ptr::Type>::Return::Type Type;
  };

  Ptr(Type *ptr) : Base((typename Base::Type *)ptr) {}
  Bool operator == (const Type *ptr) const { return *this == (typename Base::Type *)ptr; }
  Bool operator == (const typename Base::Type *ptr) const { return Base::operator == (ptr); }
  friend Bool operator == (const Type *p, const Ptr &ptr) { return ptr == p; }
  friend Bool operator != (const Type *p, const Ptr &ptr) { return !(ptr == p); }
  friend Bool operator == (const typename Base::Type *p, const Ptr &ptr) { return ptr == p; }
  friend Bool operator != (const typename Base::Type *p, const Ptr &ptr) { return !(ptr == p); }

  Ptr(const Null &ptr) : Base(ptr) { }
  Bool operator == (const Null &ptr) const { return Base::operator == (ptr); }

  Ptr &operator = (const Null &) {
    if (*this != null) {
        --(**this);
        Weak() = null;
    }
    return *this;
  }

  Ptr(const Ptr &ptr) : Base(ptr) { if (*this != null) { ++(**this); } }
  Bool operator == (const Ptr &ptr) const { return Base::operator == (ptr); }

  Ptr &operator = (const Ptr &ptr) {
    if (this != &ptr) {
      *this = null;
      Weak() = ptr;
      if (*this != null) { ++(**this); }
    }
    return *this;
  }

  ~Ptr() { *this = null; }

  Base& Weak() { return *this; }

  template <typename U, typename B>
  operator const Ptr<U, B> &() const {
    LWF::Type<Type *>().cast(LWF::Type<U *>());
    //LWF::Traits::Lame(static_cast<const U &>((const Type &)**this));
    return *(const Ptr<U, B> *)this;
  }
};

} // namespace Traits

template <typename Traits,
          typename Adjuster>
struct Ptr
  : LWF::Ptr<
    LWF::Intrusive::Traits::Ptr<Traits,
    LWF::Ptr<
    LWF::Traits::Weakless::Ptr<
    LWF::Weak::Traits::Ptr<
    LWF::Traits::Plain::Ptr<Adjuster> > > > > > {

  private: typedef
    LWF::Ptr<
    LWF::Intrusive::Traits::Ptr<Traits,
    LWF::Ptr<
    LWF::Traits::Weakless::Ptr<
    LWF::Weak::Traits::Ptr<
    LWF::Traits::Plain::Ptr<Adjuster> > > > > > Base;
  public:

  typedef typename Base::Type Type;

  Ptr(Type *ptr) : Base(ptr) {}

  Ptr(const Null &ptr = null) : Base(ptr) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U, typename A>
  Ptr(const Ptr<U, A> &ptr) : Base(ptr) {}

  template <typename U, typename A>
  Ptr &operator = (const Ptr<U, A> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }
};

}}} // namespace CShift::LWF::Intrusive


#endif // CSHIFT_LWF_INTRUSIVE_PTR_H
