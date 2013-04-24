#ifndef CSHIFT_LWF_INTEGER_H
#define CSHIFT_LWF_INTEGER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {

template <UInt bytes, typename Sign = LWF::Kind::Integer:: Signed> struct Integer {};
//template <UInt bytes> struct  Integer<bytes,  LWF::Kind::Integer::  Signed> { typedef  Int Type; };
//template <UInt bytes> struct  Integer<bytes,  LWF::Kind::Integer::Unsigned> { typedef UInt Type; };
template <> struct  Integer<1,  LWF::Kind::Integer::Signed  > { typedef  Int8  Type; };
template <> struct  Integer<1,  LWF::Kind::Integer::Unsigned> { typedef UInt8  Type; };
template <> struct  Integer<2,  LWF::Kind::Integer::Signed  > { typedef  Int16 Type; };
template <> struct  Integer<2,  LWF::Kind::Integer::Unsigned> { typedef UInt16 Type; };
template <> struct  Integer<4,  LWF::Kind::Integer::Signed  > { typedef  Int32 Type; };
template <> struct  Integer<4,  LWF::Kind::Integer::Unsigned> { typedef UInt32 Type; };
#if PLATFORM_COMPILER_64BITS_INTEGER
template <> struct  Integer<8,  LWF::Kind::Integer::Signed  > { typedef  Int64 Type; };
template <> struct  Integer<8,  LWF::Kind::Integer::Unsigned> { typedef UInt64 Type; };
#endif // C++99

namespace Signed {
template <UInt bytes> struct Integer :
    LWF::Integer<bytes, LWF::Kind::Integer::Signed> {};
}
namespace Unsigned {
template <UInt bytes> struct Integer :
    LWF::Integer<bytes, LWF::Kind::Integer::Unsigned> {};
}

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_INTEGER_H
