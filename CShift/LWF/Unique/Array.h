#ifndef CSHIFT_LWF_UNIQUE_ARRAY_H
#define CSHIFT_LWF_UNIQUE_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Traits/Array.h"
#include "LWF/Traits/Nonconst.h"
#include "LWF/Forward/reference.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Weak/Array.h"

namespace CShift {
namespace LWF {
namespace Unique {

namespace Traits {

template <typename Begin>
struct Array : LWF::Traits::Array<Begin> {
  private: typedef LWF::Traits::Array<Begin> Base; public:

  typedef typename Begin::Deleter Deleter;
  typedef typename Base::Iterator Iterator;
  struct Unique { typedef Begin Iterator; };

  struct Release {
    struct Iterator : Array::Iterator {
      Iterator (Array &array_) : array(array_) {}

      Iterator &operator = (const Null &) {
        Array::Iterator::operator = (null);
        array.begin_.Weak() = null; array = null; return *this;
      }
      private: Array &array;
    };
  };

  Deleter& owner()       { return Base::begin_.owner(); }
  const Deleter& owner() const { return Base::begin_.owner(); }

  typename Release::Iterator Weak() { return *this; }
  Iterator Weak() const { return Base::begin(); }

  #if !PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(const Begin &begin, const Iterator &end) : Base(const_cast<Begin &>(begin), end) {}
  #endif // !C++11
  ConstructionTransparency(Array, Base) {}
};

} // namespace Traits

template <typename Type,
          typename Deleter = LWF::Deleter<Type[]> >
struct Array
  : LWF::Collection::Static::Container<
    LWF::Unique::Traits::Array<LWF::Unique::Ptr<Type[], Deleter> > >  {
  private:
    typedef LWF::Unique::Ptr<Type[], Deleter> Begin;
    typedef LWF::Collection::Static::Container<
          LWF::Unique::Traits::Array<Begin> > Base;
  public: typedef
    typename Base::Iterator Iterator;

  Array(const Iterator &begin = null, Int size = 0, const Deleter &deleter = Deleter())
    : Base(Begin(&*begin, deleter), Iterator(begin + size)) {}
  Array(const Iterator &begin, const Iterator &end, const Deleter &deleter = Deleter())
    : Base(Begin(&*begin, deleter), end) {}
  Array(const Deleter &deleter)
    : Base(Begin(null, deleter), Iterator(null)) {}

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
//  TODO: public: template <typename T> friend class LWF::Traits::Mutable::Type<T>;
  operator Nonconst () { return Nonconst(*this); }
  Array(Nonconst array) : Base(array) {}
  Array &operator = (Nonconst array) { Base::operator = (array); return *this; }
  #endif // !C++11

  operator LWF::Weak::Array<Type> () const {
    return LWF::Weak::Array<Type> (Base::begin(), Base::end());
  }
  operator LWF::Weak::Array<const Type> () const {
    return LWF::Weak::Array<const Type> (Base::begin(), Base::end());
  }
};

}}} // namespace CShift::LWF::Unique

#endif // CSHIFT_LWF_UNIQUE_ARRAY_H
