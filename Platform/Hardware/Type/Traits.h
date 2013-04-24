#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Nonfundamental/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <typename T> struct Traits : Kind::Nonfundamental::Traits<T> {};

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_H
