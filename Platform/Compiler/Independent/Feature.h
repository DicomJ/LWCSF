#ifndef CSHIFT_PLATFORM_COMPILER_Independent_FEATURE_H
#define CSHIFT_PLATFORM_COMPILER_Independent_FEATURE_H

#include "Platform/Compiler/License"
#include "Author/Andriy.Bulka"

#include "LWF/Boolean/Constant.h"
//LWF

namespace CShift {
namespace Platform {
namespace Compiler {
namespace Independent {

struct Feature {

  static const Bool support64BitsInteger =
    #if PLATFORM_COMPILER_64BITS_INTEGER
      True;
    #else // !PLATFORM_COMPILER_64BITS_INTEGER
      False;
    #endif // !PLATFORM_COMPILER_64BITS_INTEGER
};

}}}} // CShift::Platform::Compiler::Independent

#endif // CSHIFT_PLATFORM_COMPILER_Independent_FEATURE_H
