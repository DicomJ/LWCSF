#ifndef PLATFORM_HARDWARE_TYPE_KIND_REAL_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_KIND_REAL_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Def.h"
#include "Platform/Hardware/Type/Kind/Real.h"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

template <typename T>
struct Real::Traits : Kind::Def<Kind::Real> {
  static const T max;
  static const T min;
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_REAL_TRAITS_H
