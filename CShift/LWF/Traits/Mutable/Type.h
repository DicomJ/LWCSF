#ifndef CSHIFT_LWF_TRAITS_MUTABLE_TYPE_H
#define CSHIFT_LWF_TRAITS_MUTABLE_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Is.Has.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Mutable {

template<typename T>
class Type {
  template<typename U> static Is    &criterion(typename U::Nonconst *);
  template<typename  > static Isnot &criterion(...);
  public: static const Bool nonconst = sizeof(criterion<T>(0)) == sizeof(Is);
};

}}}} // namespace CShift::Traits::Mutable

#endif // CSHIFT_LWF_TRAITS_MUTABLE_TYPE_H
