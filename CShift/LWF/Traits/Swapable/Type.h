#ifndef CSHIFT_LWF_TRAITS_SWAPABLE_TYPE_H
#define CSHIFT_LWF_TRAITS_SWAPABLE_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Is.Has.h"
#include "LWF/Traits/Match/Value.h"
#include "LWF/Traits/Exclusively/Nonfundamental.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Swapable {

template <typename T>
class Type {
  struct Prototype { Void swap(){} };
  struct Ambiguous : LWF::Traits::Exclusively::Nonfundamental<T>, Prototype {};
  template <typename U>
  static LWF::Traits::Isnot criterion(U *,
   LWF::Traits::Match::Value<Void (Prototype::*)(), &U::swap> * = 0);
  static LWF::Traits::Is    criterion(...);

  public: static const Bool swapable =
    (sizeof(criterion((Ambiguous*)0)) == sizeof(LWF::Traits::Is));
};

}}}} // namespace CShift::Traits::Swapable

#endif // CSHIFT_LWF_TRAITS_SWAPABLE_TYPE_H
