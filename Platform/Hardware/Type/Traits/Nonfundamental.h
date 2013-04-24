#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_NONFUNDAMENTAL_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_NONFUNDAMENTAL_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Nonfundamental.h"
#include "Platform/Hardware/Type/Kind/Nonfundamental/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <> struct Traits<Nonfundamental::Void>
    : Kind::Nonfundamental::Traits<Nonfundamental::Void> {};

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_NONFUNDAMENTAL_H
