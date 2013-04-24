#ifndef PLATFORM_HARDWARE_TYPE_CHARACTER_H
#define PLATFORM_HARDWARE_TYPE_CHARACTER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Character {

namespace Select {

template <int size, bool charSigned = (char(-1) < 0)> struct Char;

template <bool charSigned> struct Char< 8, charSigned > { typedef char Type; };
#if PLATFORM_COMPILER_UCHAR
template <bool charSigned> struct Char<16, charSigned > { typedef char16_t Type; };
template <bool charSigned> struct Char<32, charSigned > { typedef char32_t Type; };
#else
template <> struct Char<16, false> { typedef unsigned short int  Type; };
template <> struct Char<16, true > { typedef signed   short int  Type; };
template <> struct Char<32, false> { typedef unsigned       int  Type; };
template <> struct Char<32, true > { typedef signed         int  Type; };
#endif

} // namespace Select

typedef Select::Char<8 >::Type Char8;
typedef Select::Char<16>::Type Char16;
typedef Select::Char<32>::Type Char32;
typedef                wchar_t WChar;

// TODO: Platform specific
typedef Char8 Char;
//typedef WChar Char;

}}}} // namespace Platform::Hardware::Type::Character

#endif // PLATFORM_HARDWARE_TYPE_CHARACTER_H
