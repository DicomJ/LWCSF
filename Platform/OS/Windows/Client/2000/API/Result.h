#ifndef CSHIFT_PLATFORM_OS_API_RESULT_H
#define CSHIFT_PLATFORM_OS_API_RESULT_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Base.h"

#include "LWF/Type.h"
#include "LWF/Exception.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct Result {

  struct Exception : LWF::Exception {
    Exception(const Result &result) {
      error = result ? ERROR_SUCCESS : GetLastError();
    }

    virtual const Char8 *what() const throw() {

      LPVOID lpMsgBuf;

      FormatMessage(
              FORMAT_MESSAGE_ALLOCATE_BUFFER |
              FORMAT_MESSAGE_FROM_SYSTEM |
              FORMAT_MESSAGE_IGNORE_INSERTS,
              NULL,
              error,
              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
              (LPTSTR) &lpMsgBuf,
              0, NULL );

      return ""; // TODO: convert (LPTSTR) to Char8 *
    }

    DWORD error;
  };

  Result(BOOL result_) : result(result_) {
    if (!result) { LWF::Exception::Throw(Exception(*this)); }
  }

  operator Bool() const { return result; }

  private: Bool result;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_RESULT_H
