#ifndef CSHIFT_LWF_WEAK_PTR_H
#define CSHIFT_LWF_WEAK_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Null.h"
#include "LWF/Traits/Subscriptable/Ptr.h"
#include "LWF/Traits/Weakness/Ptr.h"
#include "LWF/Ptr.h"


namespace CShift {
namespace LWF {
namespace Weak {

namespace Traits {

template <typename Base>
struct Ptr : LWF::Traits::Lvalue::Ptr<Base>
{
  typedef typename Base::Type Type;
  
  Ptr(Type *ptr_) : ptr(ptr_) { }
  Type & operator * () const { return *this->ptr; }
  Bool operator == (const Type *ptr) const { return this->ptr == ptr; }
  friend Bool operator == (const Type *p, const Ptr &ptr) { return ptr == p; }
  friend Bool operator != (const Type *p, const Ptr &ptr) { return !(ptr == p); }

  Ptr(const Null &ptr) { *this = ptr; }
  Ptr &operator = (const Null &) { this->ptr = (Type *)(0); return *this; }
  Bool operator == (const Null &) const { return (Type *)0 == &**this; }

  Ptr(const Ptr &ptr) { *this = ptr; }
  Ptr &operator = (const Ptr &ptr) { this->ptr = ptr.ptr; return *this; }
  Bool operator == (const Ptr &ptr) const { return &**this == &*ptr; }

  template <typename U>
  operator const Ptr<U>&() const {
    LWF::Type<typename Base::Unbiased::Type *>().cast(
    LWF::Type<typename U   ::Unbiased::Type *>());
    return *(const Ptr<U> *)this;
  }

  typedef Ptr Caster;

  private: Type *ptr;
};

} // namespace Traits

template <typename Traits>
struct Ptr
  : LWF::Ptr<
    LWF::Traits::Weakness::Ptr<
    LWF::Weak::Traits::Ptr<
    LWF::Traits::Subscriptable::Ptr<Traits> > > >
{
  private: typedef
    LWF::Ptr<
    LWF::Traits::Weakness::Ptr<
    LWF::Weak::Traits::Ptr<
    LWF::Traits::Subscriptable::Ptr<Traits> > > > Base;
  public: typedef
   typename Base::Type Type;

  Ptr(Type *ptr) : Base(ptr) {}

  Ptr(const Null &ptr = null) : Base(ptr) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U>
  Ptr(const Ptr<U> &ptr) : Base(ptr) {}

  template <typename U>
  Ptr &operator = (const Ptr<U> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }

  operator Ptr<const Traits> () const { return Ptr<const Traits>(&**this); }
};


template <typename Traits>
struct Ptr <Traits[]>: LWF::Ptr<
    LWF::Traits::Weakness::Ptr<
    LWF::Weak::Traits::Ptr<
    LWF::Traits::Subscriptable::Ptr<Traits[]> > > > {

  typedef  LWF::Ptr<
           LWF::Traits::Weakness::Ptr<
           LWF::Weak::Traits::Ptr<
           LWF::Traits::Subscriptable::Ptr<Traits[]> > > > Base;

  typedef typename Base::Type Type;

  Ptr(Type *ptr) : Base(ptr) {}

  Ptr(const Null &ptr = null) : Base(ptr) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U>
  Ptr(const Ptr<U> &ptr) : Base(ptr) {}

  template <typename U>
  Ptr &operator = (const Ptr<U> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }

  operator Ptr<const Traits[]> () const { return Ptr<const Traits[]>(&**this); }

  WeaknessTransparency(Ptr, Base){}
};

//WeaknessTransparency

template <typename Type>
struct Cast {
  typedef Type Ptr;
  //struct Recursive { typedef Cast::Ptr Ptr; };
  struct Range { typedef Type Ptr; };
};

template <typename Type>
struct Cast<Type*> {
  typedef LWF::Weak::Ptr<Type> Ptr;                                             // T *  => Weak::Ptr<T>
  //struct Recursive {
  //  typedef LWF::Weak::Ptr<typename LWF::Weak::Cast<Type>::Recursive::Ptr> Ptr; // [T [*...]*  => [ Weak::Ptr< ] ... Weak::Ptr<T> ...  [ > ]
  //};
  struct Range {
    typedef LWF::Weak::Ptr<Type[]> Ptr;                                         // T *  => Weak::Ptr<T[]>
  };
};

template <typename Type>
struct Cast<Type[]> {
  typedef LWF::Weak::Ptr<Type[]> Ptr;                                           // T []  => Weak::Ptr<T[]>
  //struct Recursive {
  //  typedef LWF::Weak::Ptr<typename LWF::Weak::Cast<Type>::Recursive::Ptr[]> Ptr;
  //};
  struct Range {
    typedef LWF::Weak::Ptr<Type[]> Ptr;                                         // // T []  => Weak::Ptr<T[]>
  };
};

template <typename Type, UInt N>
struct Cast<Type[N]>  : Cast<Type[]> {};

}}} // namespace CShift::LWF::Weak

#endif // CSHIFT_LWF_WEAK_PTR_H
