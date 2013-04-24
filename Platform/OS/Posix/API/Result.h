#ifndef CSHIFT_PLATFORM_OS_API_RESULT_H
#define CSHIFT_PLATFORM_OS_API_RESULT_H

#include "LWF/Type.h"
#include "LWF/Exception.h"

#include <string.h>
#include <errno.h>

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct Result {

  struct Exception : CShift::LWF::Exception {
    Exception(const Result &result) : error(result.error) { }
    /*virtual */const Char8 *what() const throw() { return strerror(error); }
    Int error;
  };

  Result(Int error) : error(error) {
    if (!*this) { LWF::Exception::Throw(Exception(*this)); }
  }

  static Result asBool(Bool success) { return Result(success ? 0 : errno); }

  static Bool except(Int result, Int exception, Bool asResult = False) {
    return result != exception ? (Bool)Result(result) : asResult;
  }

  operator Bool() const { return 0 == error; }
  private: Int error;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_RESULT_H
