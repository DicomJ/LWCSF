#ifndef CSHIFT_LWF_TRAITS_SIZEOF_TYPE_H
#define CSHIFT_LWF_TRAITS_SIZEOF_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Sizeof {

template <typename T>
struct Type {
  static const UInt size = sizeof(T);
};

template <typename T>
struct Type<T[]> {
  static const UInt size = sizeof(Void *);
};

template <>
struct Type<Void> {
  static const UInt size = 0;
};

}}}} // namespace CShift::LWF::Traits::Sizeof

#endif // CSHIFT_LWF_TRAITS_SIZEOF_TYPE_H
