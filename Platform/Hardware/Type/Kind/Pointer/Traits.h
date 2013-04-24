#ifndef PLATFORM_HARDWARE_TYPE_KIND_POINTER_TRAITS_H
#define PLATFORM_HARDWARE_TYPE_KIND_POINTER_TRAITS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Kind/Def.h"
#include "Platform/Hardware/Type/Kind/Pointer.h"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

template <typename T>
struct Pointer::Traits : public Kind::Def<Kind::Pointer> {
  struct Value { typedef T Type; };
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_POINTER_TRAITS_H
