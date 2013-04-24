#ifndef CSHIFT_LWF_STATIC_UNIQUE_ARRAY_H
#define CSHIFT_LWF_STATIC_UNIQUE_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Static/Traits/Array.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Static/Weak/Array.h"

namespace CShift {
namespace LWF {
namespace Static {
namespace Unique {

namespace Traits {

template <typename Begin, UInt size>
struct Array : LWF::Static::Traits::Array<Begin, size> {
  private: typedef LWF::Static::Traits::Array<Begin, size> Base; public:

  typedef typename Begin::Deleter Deleter;
  typedef typename Base::Iterator Iterator;
  struct Unique { typedef Begin Iterator; };

  Iterator &Weak() { return Base::begin_.Weak(); }
  Iterator Weak() const { return Base::begin(); }

  #if !PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(const Begin &begin) : Base(const_cast<Begin &>(begin)) {}
  #endif // !C++11
  ConstructionTransparency(Array, Base) {}
};

} // namespace Traits

template <typename Type, UInt size,
          typename Deleter = LWF::Deleter<Type[]> >
struct Array
  : LWF::Collection::Static::Container<
    LWF::Static::Unique::Traits::Array<
      LWF::Unique::Ptr<Type[], Deleter>, size > >
{
  private: typedef
    LWF::Unique::Ptr<Type[], Deleter> Begin;
  private: typedef
    LWF::Collection::Static::Container<
    LWF::Static::Unique::Traits::Array<Begin, size > > Base;
  public: typedef
    typename Base::Iterator Iterator;

  Array(const Iterator &begin = null, const Deleter &deleter = Deleter())
    : Base(Begin(&*begin, deleter)) { }
  Array(const Deleter &deleter) : Base(Begin(null, deleter)) {}

  Array &operator = (const Null &) { Base::operator = (null); return *this; }

  Array(Array &array) : Base(array) {}
  Array &operator = (Array &array) { Base::operator = (array); return *this; }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(Array &&array) : Base(LWF::Forward::reference<Base>(array)) {}
  Array &operator = (Array &&array) {
    Base::operator = (LWF::Forward::reference<Base>(array)); return *this;
  }
  #else // !C++11
  public: typedef LWF::Traits::Nonconst<Base> Nonconst;
  public: // TODO make Nonconst private
  operator Nonconst () { return Nonconst(*this); }
  Array(Nonconst array) : Base(array) {}
  Array &operator = (Nonconst array) { Base::operator = (array); return *this; }
  #endif // !C++11*/

  operator LWF::Static::Weak::Array<Type, size> () const {
    return LWF::Static::Weak::Array<Type, size> (Base::begin());
  }
  operator LWF::Static::Weak::Array<const Type, size> () const {
    return LWF::Static::Weak::Array<const Type, size> (Base::begin());
  }
};

}}}} // namespace CShift::LWF::Static::Unique

#endif // CSHIFT_LWF_STATIC_UNIQUE_ARRAY_H
