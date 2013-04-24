#ifndef CSHIFT_PLATFORM_OS_API_STRING_H
#define CSHIFT_PLATFORM_OS_API_STRING_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Base.h"

#if defined(UNICODE)
# include "Text/Wide/String.h"
#else  // !defined(UNICODE)
# include "Text/ASCII/String.h"
#endif // !defined(UNICODE)

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

#if defined(UNICODE)
typedef Text::Wide::String String;
#else  // !defined(UNICODE)
typedef Text::ASCII::String String;
#endif // !defined(UNICODE)

struct Optional {
  static LPCTSTR lpctstr(const String &string) {
    return string.empty() ? NULL : &*string.cstring();
  }
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_STRING_H
