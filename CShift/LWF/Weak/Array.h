#ifndef CSHIFT_LWF_WEAK_ARRAY_H
#define CSHIFT_LWF_WEAK_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Traits/Array.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Forward/reference.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Range.h"

namespace CShift {
namespace LWF {
namespace Weak {

template <typename Type>
struct Array
  : LWF::Collection::Static::Container<
      LWF::Traits::Array<LWF::Weak::Ptr<Type[]> > >
{
  private: typedef
    LWF::Collection::Static::Container<
      LWF::Traits::Array<LWF::Weak::Ptr<Type[]> > > Base;
  public: typedef
    typename Base::Iterator Iterator;

  Array(const Iterator &begin = null, UInt size = 0): Base(begin, begin + size) {}
  Array(const Iterator &begin, const Iterator &end) : Base(begin, end) {}
  Array(const LWF::Range<Iterator> &range) : Base(range.begin(), range.end()) {}

  Array &operator = (const Null &) { Base::operator = (null); return *this; }

  Array &operator = (const Array &array) {
    Base::operator = (array); return *this;
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array &operator = (Array &&array) {
    Base::operator = (LWF::Forward::reference<Array>(array)); return *this;
  }
  #endif // C++11

  operator Array<const Type> () const {
    return Array<const Type>(Base::begin(), Base::end());
  }
};

}}} // namespace CShift::LWF::Weak

#endif // CSHIFT_LWF_WEAK_ARRAY_H
