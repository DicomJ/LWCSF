#ifndef CSHIFT_LWF_STATIC_WEAK_ARRAY_H
#define CSHIFT_LWF_STATIC_WEAK_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Static/Traits/Array.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {
namespace Static {
namespace Weak {

template <typename Type, UInt size>
struct Array
  : LWF::Collection::Static::Container<
    LWF::Static::Traits::Array <
    LWF::Weak::Ptr<Type[]>, size > >
{
  private: typedef
    LWF::Collection::Static::Container<
    LWF::Static::Traits::Array <
    LWF::Weak::Ptr<Type[]>, size > > Base;
  public: typedef
    typename Base::Iterator Iterator;

  Array(const Iterator &begin = null) : Base(begin) { }

  Array &operator = (const Null &) { Base::operator = (null); return *this; }

  Array &operator = (const Array &array) {
    Base::operator = (array); return *this;
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array &operator = (Array &&array) {
    Base::operator = (LWF::Forward::reference<Array>(array)); return *this;
  }
  #endif // C++11

  operator Array<const Type, size> () const {
    return Array<const Type, size>(Base::begin());
  }
};

}}}} // namespace CShift::LWF::Static::Weak

#endif // CSHIFT_LWF_STATIC_WEAK_ARRAY_H
