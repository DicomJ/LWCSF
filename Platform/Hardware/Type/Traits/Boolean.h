#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_BOOLEAN_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_BOOLEAN_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Boolean.h"
#include "Platform/Hardware/Type/Kind/Boolean/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <> struct Traits<Boolean::Bool>
    : Kind::Boolean::Traits<Boolean::Bool> {};
  
}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_BOOLEAN_H
