#ifndef PLATFORM_HARDWARE_TYPE_KIND_CHARACTER_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_KIND_CHARACTER_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Def.h"
#include "Platform/Hardware/Type/Kind/Character.h"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

template <typename T>
struct Character::Traits : Kind::Def<Kind::Character> {
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_CHARACTER_TRAITS_H
