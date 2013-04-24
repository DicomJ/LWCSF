#ifndef PLATFORM_HARDWARE_TYPE_INTEGER_H
#define PLATFORM_HARDWARE_TYPE_INTEGER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Integer {

typedef signed              char  Int8;
typedef unsigned            char  UInt8;

typedef signed    short     int   Int16;
typedef unsigned  short     int   UInt16;

typedef signed              int   Int32;
typedef unsigned            int   UInt32;

#if PLATFORM_COMPILER_64BITS_INTEGER // todo: separate to another file
typedef signed    long long int   Int64;
typedef unsigned  long long int   UInt64;
#endif
#ifdef PLATFORM_COMPILER_128BITS_INTEGER
//#if PLATFORM_COMPILER_128BITS_INTEGER // todo: consider 128 bit
#endif

// Takes exactly 8 bits
typedef UInt8                     Byte;

// Mechine word wide definition
typedef signed    long      int   Int;
typedef unsigned  long      int   UInt;

// The longest/largest possible machine integer definition
#ifdef PLATFORM_COMPILER_128BITS_INTEGER
//#if PLATFORM_COMPILER_128BITS_INTEGER // todo: consider 128 bit
#elif PLATFORM_COMPILER_64BITS_INTEGER
typedef Int64                     LInt;
typedef UInt64                    LUInt;
#else
typedef Int32                     LInt;
typedef UInt32                    LUInt;
#endif // C++99

}}}} // namespace Platform::Hardware::Type::Integer

#endif // PLATFORM_HARDWARE_TYPE_INTEGER_H
