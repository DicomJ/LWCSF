#ifndef CSHIFT_LWF_TYPE_H
#define CSHIFT_LWF_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Type.h"
#include "LWF/Traits/Const/Type.h"
#include "LWF/Traits/Sizeof/Type.h"

#include "LWF/Traits/Swapable/Type.h"
#include "LWF/Traits/Mutable/Type.h"
#include "LWF/Traits/Rangable/Type.h"
#include "LWF/Traits/Castable/Types.h"
#include "LWF/Traits/Derived/Types.h"
#include "LWF/Traits/Match/Type.h"
#include "LWF/Type/cast.h"


namespace CShift {
namespace LWF {

template <typename T>
struct Type : LWF::Traits::Type<T>,
              LWF::Traits::Const::Type<T>,
              LWF::Traits::Sizeof::Type<T> {

  static const UInt sizeInBits = 8 * LWF::Traits::Sizeof::Type<T>::size;

  #if PLATFORM_COMPILER_CONSTEXPR
  constexpr
  #endif // C++11
  Bool operator == (const Type &) {
    return LWF::Kind::Boolean::Traits<Bool>::True;
  }
  template<typename U>
  #if PLATFORM_COMPILER_CONSTEXPR
  constexpr
  #endif // C++11
  Bool operator == (const Type<U> &) {
    return  LWF::Kind::Boolean::Traits<Bool>::False;
  }
  template<typename U>
  #if PLATFORM_COMPILER_CONSTEXPR
  constexpr
  #endif // C++11
  Bool operator != (const Type<U> &type) {
    return  !(*this == type);
  }

  struct Is;

  template <typename Item>
  struct Holds { static const UInt items = sizeof(T) / sizeof(Item); };

  template <typename Item>
  struct Occupies { static const UInt items = Holds<Item>::items + (sizeof(T) % sizeof(Item)? 1 : 0); };

  Void cast/*to specified type*/(const Type &) const {}
  template<typename U>
  Void cast/*to specified type*/(const Type<U> &) const {
    /*TODO*/
  }
};

template <typename T>
struct Type<T>::Is :
  LWF::Traits::Swapable::Type<T>,
  LWF::Traits::Rangable::Type<T>,
  LWF::Traits::Mutable::Type<T> {
  struct Equal { template <typename TT> struct To {
    static const Bool type = LWF::Traits::Match::Type<T, TT>::equal; }; };
  struct Castable { template <typename TT> struct To {
    static const Bool type = LWF::Traits::Cast::By::Kind<T, TT>::isCastible; }; };
  struct Base { template <typename TT> struct Of {
    static const Bool type = LWF::Traits::Derived::Types<T, TT>::base; }; };
  static const Bool nonfundamental =
      LWF::Traits::Match::Type<typename LWF::Type<T>::Kind,
                               LWF::Kind::Nonfundamental>::equal;
  static const Bool fundamental = !nonfundamental;
};

namespace Kind {

template <typename T>
struct Type : LWF::Type<typename LWF::Type<T>::Kind> {};

} // namespace Kind

namespace Sign {

template <typename T>
struct Type : LWF::Type<typename LWF::Type<T>::Sign> {};

} // namespace Sign

}} // CShift::LWF


#endif // CSHIFT_LWF_TYPE_H
