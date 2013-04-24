#ifndef CSHIFT_LWF_MOVE_PTR_H
#define CSHIFT_LWF_MOVE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Ptr.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Placement/Allocator.h"
#include "LWF/Placement/Deleter.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Forward/reference.h"
#include "LWF/Move/reference.h"


namespace CShift {
namespace LWF {
namespace Move {

namespace Traits {

template <typename Type>
struct Value : LWF::Traits::Prototype{};

template <typename Type>
struct Value<Type &>/* : Type */ {
  Value &operator = (const Type &value) { new (this) Type(value); return *this; }
  Value &operator = (      Type &value) { new (this) Type(value); return *this; }
#if PLATFORM_COMPILER_RVALUE_REFERENCE
  Value &operator = (Type &&value) {
    new (this) Type(LWF::Forward::reference<Type>(value));
    return *this;
  }
#endif // C++11

  Value &operator = (Value &value) {
    *this = LWF::Move::reference(value.type());
    value = null;
    return *this;
  }

  Void operator = (const Null &) {
    LWF::Unique::Ptr<Type, LWF::Placement::Deleter<Type> > deleter(&type());
  }

#if PLATFORM_COMPILER_RVALUE_REFERENCE
  operator Type && () {
    return LWF::Move::reference(reinterpret_cast<Type &>(*this));
  }
#else // !C++11
  operator Type & () {
    return LWF::Move::reference(reinterpret_cast<Type &>(*this));
  }
#endif // !C++11

  private: Type& type() { return reinterpret_cast<Type &>(*this); }
};

template <typename Base_>
struct Ptr : Base_ {
  private: typedef Base_ Base;
  public: typedef LWF::Move::Traits::Value<typename Base::Return::Type> Type;
  struct Return {
    typedef typename LWF::Traits::Uvalue::Ptr<Base, typename Ptr::Type>::Return::Type Type;
  };
  Ptr() {}
  PtrConstructionTransparency() {}

  typename Return::Type operator * () const {
    return reinterpret_cast<typename Return::Type>(Base::operator * ());
  }
};

} // namespace Traits

template <typename Traits >
struct Ptr : LWF::Ptr<
             LWF::Move::Traits::Ptr<
             typename LWF::Weak::Cast<Traits>::Ptr> >
{
  private: typedef
    LWF::Ptr<
    LWF::Move::Traits::Ptr<
    typename LWF::Weak::Cast<Traits>::Ptr> > Base;
  public:

  Ptr() {}
  PtrConstructionTransparency() {}
};

template <typename Ptr>
LWF::Move::Ptr<Ptr> ptr(const Ptr &ptr) { return ptr; }


namespace { template <typename T> struct Conception {
  T value;
  const T& cvalue;
  Byte allocated[sizeof(T)];
  LWF::Move::Ptr<T> move;
  Conception() : cvalue(value), move((T *)allocated) {}

  Void Construction() {
    *move = value;  // new ((Void *)allocated) T(T &value)
    *move = cvalue; // new ((Void *)allocated) T(const T &cvalue)
    *move = LWF::Move::reference<T>(value); // new ((Void *)allocated) T(T &&value);
  }

  Void Casting() {
    value = *move; // value = Move::reference<T>(value)
  }

  Void Sliding() {
    *move = *LWF::Move::ptr(&value); // new ((Void *)allocated) T(T &&value); value.~T();
  }
  Void Destroying() {
    *move = null; // ~T();
  }
};}

}}} // namespace CShift::LWF::Move

#endif // CSHIFT_LWF_MOVE_PTR_H
