#ifndef CSHIFT_LWF_DEBUG_ASSERT_H
#define CSHIFT_LWF_DEBUG_ASSERT_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Debug.h"
#include "LWF/Exception.h"

namespace CShift {
namespace LWF {

struct Debug::Assert {

  struct Exception : LWF::Exception {

    virtual const Char8 *what() const throw() {
      return "Assert::Exception"; // TODO: return a callstack list
    }
  };

#if BUILD_DEBUG
  Assert(Bool truth) { assert(truth, Assert::Exception()); }
  template<typename E>
  Assert(Bool truth, const E &e) { assert(truth, e); }
#else
  Assert(Bool) {}
  template<typename E>
  Assert(Bool, const E & = E()) {}
#endif
  private: template<typename E>
  Void assert(Bool truth, const E &e) {
    if (!truth) {
      if (1) {
        Int i = 0, n = 0 / i; if (i != n) {}
      } else {
        LWF::Exception::Throw(e);
      }
    }
  }
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_DEBUG_H
