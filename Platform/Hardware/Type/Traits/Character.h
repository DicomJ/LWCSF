#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_CHARACTER_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_CHARACTER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Character.h"
#include "Platform/Hardware/Type/Kind/Character/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <> struct
Traits<Character::Char8> : Kind::Character::Traits<Character::Char8> {};
#if PLATFORM_COMPILER_UCHAR
template <> struct
Traits<Character::Char16> : Kind::Character::Traits<Character::Char16> {};
template <> struct
Traits<Character::Char32> : Kind::Character::Traits<Character::Char32> {};
#endif
template <> struct
Traits<Character::WChar> : Kind::Character::Traits<Character::WChar> {};

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_CHARACTER_H
