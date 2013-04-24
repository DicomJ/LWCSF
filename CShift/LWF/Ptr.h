#ifndef CSHIFT_LWF_PTR_H
#define CSHIFT_LWF_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Ptr.h"


namespace CShift {
namespace LWF {

template <typename Base_>
struct Ptr : Base_ {
  private: typedef Base_ Base; public:

  typedef typename Base::Type Type;
  struct Return { typedef typename Base::Return::Type Type; };

  typename Return::Type operator * () const { return Base::operator * (); }
  Type *operator ->() const { return &**this; }

  Ptr operator + (Int index) const { return Base::operator + (index); }
  Ptr operator - (Int index) const { return *this + -index; }

  Ptr& operator += (Int index) { return *this = (*this + index); }
  Ptr& operator -= (Int index) { return *this += -index; }

  Ptr& operator ++ () { return *this += 1; }
  Ptr& operator -- () { return *this -= 1; }
  Ptr operator ++ (Int32) { Ptr ptr(*this); ++*this; return ptr; }
  Ptr operator -- (Int32) { Ptr ptr(*this); --*this; return ptr; }

  typename Return::Type operator [] (Int index) const { return Base::operator[] (index); }

  Int operator - (const Ptr &ptr) const { return Base::operator - (ptr); }

  Bool operator >  (const Ptr &ptr) const { return (*this - ptr) >  0; }
  Bool operator >= (const Ptr &ptr) const { return (*this - ptr) >= 0; }
  Bool operator <  (const Ptr &ptr) const { return ptr > *this;  }
  Bool operator <= (const Ptr &ptr) const { return ptr >= *this; }

  template <typename U>
  Bool operator == (const U &u) const { return Base::operator == (u); }
  template <typename U>
  Bool operator != (const U &u) const { return !(*this == u); }

  Ptr() {}
  PtrConstructionTransparency() {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_PTR_H
