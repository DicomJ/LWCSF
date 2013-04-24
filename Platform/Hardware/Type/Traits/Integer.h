#ifndef PLATFORM_HARDWARE_TYPE_TRAITS_INTEGER_H
#define PLATFORM_HARDWARE_TYPE_TRAITS_INTEGER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits.h"
#include "Platform/Hardware/Type/Integer.h"
#include "Platform/Hardware/Type/Kind/Integer/Traits.h"


namespace Platform {
namespace Hardware {
namespace Type {

template <> struct
Traits<Integer::Int> : Kind::Integer::Traits<Integer::Int> {};
template <> struct
Traits<Integer::UInt> : Kind::Integer::Traits<Integer::UInt> {};

template <> struct
Traits<Integer::Int8> : Kind::Integer::Traits<Integer::Int8> {};
template <> struct
Traits<Integer::UInt8> : Kind::Integer::Traits<Integer::UInt8> {};

template <> struct
Traits<Integer::Int16> : Kind::Integer::Traits<Integer::Int16> {};
template <> struct
Traits<Integer::UInt16> : Kind::Integer::Traits<Integer::UInt16> {};

template <> struct
Traits<Integer::Int32> : Kind::Integer::Traits<Integer::Int32> {};
template <> struct
Traits<Integer::UInt32> : Kind::Integer::Traits<Integer::UInt32> {};

#if PLATFORM_COMPILER_64BITS_INTEGER
template <> struct
Traits<Integer::Int64> : Kind::Integer::Traits<Integer::Int64> {};
template <> struct
Traits<Integer::UInt64> : Kind::Integer::Traits<Integer::UInt64> {};
#endif // C++99

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_TRAITS_INTEGER_H
