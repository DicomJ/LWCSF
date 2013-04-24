#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_POINTER_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_POINTER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Pointer.h"
#include "Platform/Hardware/Type/Kind/Pointer/Traits.h"
#include "Platform/Hardware/Type/Traits/Boolean.h"
#include "Platform/Hardware/Type/Integer.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <typename Pointer> struct Traits<Pointer*> :
    Kind::Pointer::Traits<Pointer> {
  static const Boolean::Bool subscriptible =
    Type::Kind::Boolean::Traits<Type::Boolean::Bool>::False;
};
template <typename Pointer> struct Traits<Pointer[]> :
    Kind::Pointer::Traits<Pointer> {
  static const Boolean::Bool subscriptible =
         Type::Kind::Boolean::Traits<Boolean::Bool>::True;
};
template <typename Pointer, Integer::Int N> struct Traits<Pointer[N]> :
    Kind::Pointer::Traits<Pointer> {
  static const Boolean::Bool subscriptible =
         Type::Kind::Boolean::Traits<Boolean::Bool>::True;
};

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_POINTER_H
