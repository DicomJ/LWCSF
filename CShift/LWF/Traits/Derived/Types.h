#ifndef CSHIFT_LWF_TRAITS_DERIVED_TYPES_H
#define CSHIFT_LWF_TRAITS_DERIVED_TYPES_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Is.Has.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Derived {

template <typename T, typename TT>
struct Types {
  template <typename U, typename UU>
  struct Cast { operator U * () const; operator UU * (); };
  template <typename U>
  static Is check(TT*, U);
  static Isnot check(T*, Int);
  static const Bool base = sizeof(check(Cast<T,TT>(), Int())) == sizeof(Is);
};

}}}} // namespace CShift::Traits::Derived

#endif // CSHIFT_LWF_TRAITS_DERIVED_TYPES_H
