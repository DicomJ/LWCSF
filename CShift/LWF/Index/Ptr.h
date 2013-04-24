#ifndef CSHIFT_LWF_INDEX_PTR_H
#define CSHIFT_LWF_INDEX_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Ptr.h"
#include "LWF/Traits/Plain/Ptr.h"
#include "LWF/Traits/Prototype.h"
#include "LWF/Traits/Weakness/Transparency.h"
#include "LWF/Integer.h"


namespace CShift {
namespace LWF {
namespace Index {

namespace Traits {

template <typename Traits,
          Bool integer = LWF::Type<typename LWF::Type<typename Traits::Type>::Kind>
                          ::Is::Equal::template To<LWF::Kind::Integer>::type ||
                          LWF::Type<typename LWF::Type<typename Traits::Type>::Kind>
                                                    ::Is::Equal::template To<LWF::Kind::Character>::type>
struct Ptr : LWF::Traits::Rvalue::Ptr<Traits> {
  private: typedef LWF::Traits::Rvalue::Ptr<Traits> Base; public:
  static const Bool weakness = True;
  typedef typename Traits::Type Type;

  Ptr(const Null & = null) { *this = null; }
  Ptr &operator = (const Null &) { index = 0; return *this; }
  Bool operator  == (const Null &) { return 0 == index; }

  Ptr(const Type &index) { this->index = index; }

  typename Base::Return::Type operator * () const { return index; }
  Ptr operator + (Int index) const { return this->index + index; }
  Int operator - (const Ptr &ptr) const { return index - typename LWF::Signed::template Integer<sizeof(Type)>::Type(ptr.index); }
  Bool operator  == (const Ptr &ptr) const { return index == ptr.index; }
  typename Base::Return::Type operator [] (Int index) const { return *(*this + index); }

  private: Type index;
};

template <typename Traits>
struct Ptr<Traits, False> : LWF::Traits::Prototype {};

} // namespace Traits

template <typename Type = Int>
struct Ptr
  : LWF::Ptr<LWF::Index::Traits::Ptr<LWF::Traits::Plain::Ptr<Type > > >
{
  private: typedef
    LWF::Ptr<LWF::Index::Traits::Ptr<LWF::Traits::Plain::Ptr<Type > > > Base;
  public:

  Ptr() {}
  PtrConstructionTransparency() {}
  WeaknessTransparency(Ptr, Base) {}
};

template <typename Type>
LWF::Index::Ptr<Type> ptr(const Type &index) { return index; }

}}} // namespace CShift::LWF::Index

#endif // CSHIFT_LWF_INDEX_PTR_H
