#ifndef PLATFORM_HARDWARE_TYPE_KIND_INTEGER_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_KIND_INTEGER_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Def.h"
#include "Platform/Hardware/Type/Kind/Integer.h"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

template <typename T>
struct Integer::Traits<T, /*bool IsSigned = */true> : Integer::Signed::Traits<T> {};

template <typename T>
struct Integer::Traits<T, /*bool IsSigned = */false> : Integer::Unsigned::Traits<T> {};

template <typename T>
struct Integer::Unsigned::Traits : Kind::Def<Kind::Integer> {
  typedef Integer::Unsigned Sign;
  static const T min = T(0);
  static const T max = ~min;
};

template <typename T>
struct Integer::Signed::Traits : Kind::Def<Kind::Integer> {
  typedef Integer::Signed Sign;
  static const T min = T(T(1) << (8 * sizeof(T) - 1));
  static const T max = ~min;
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_INTEGER_TRAITS_H
