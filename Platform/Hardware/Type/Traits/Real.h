#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_REAL_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_REAL_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Real.h"
#include "Platform/Hardware/Type/Kind/Real/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <> struct Traits<Real::Float  > : Kind::Real::Traits<Real::Float  > {};
template <> struct Traits<Real::Double > : Kind::Real::Traits<Real::Double > {};
template <> struct Traits<Real::LDouble> : Kind::Real::Traits<Real::LDouble> {};

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_REAL_H
