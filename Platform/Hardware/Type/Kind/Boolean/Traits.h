#ifndef PLATFORM_HARDWARE_TYPE_KIND_BOOLEAN_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_KIND_BOOLEAN_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Def.h"
#include "Platform/Hardware/Type/Kind/Boolean.h"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

template <typename T>
struct Boolean::Traits : Kind::Def<Kind::Boolean> {

  static const T False = static_cast<T>(0 != 0);
  static const T True = static_cast<T> (!False);
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_BOOLEAN_TRAITS_H
