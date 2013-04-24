#ifndef CSHIFT_LWF_TRAITS_CASTABLE_TYPES_H
#define CSHIFT_LWF_TRAITS_CASTABLE_TYPES_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Is.Has.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Castable {

template <typename T, typename ToType>
class Types {
  static LWF::Traits::Is    criterion(const ToType &);
  static LWF::Traits::Is    criterion(      ToType &);
  static LWF::Traits::Isnot criterion(...);
  static T & t();
  public: static const Bool byOperator =
            (sizeof(criterion(t())) == sizeof(LWF::Traits::Is));
};

}}}} // namespace CShift::Traits::Castable

#endif // CSHIFT_LWF_TRAITS_CASTABLE_TYPES_H
