#ifndef CSHIFT_LWF_EXCEPTION_H
#define CSHIFT_LWF_EXCEPTION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
  

namespace CShift {
namespace LWF {

struct Exception {
  Exception() throw() {}
  virtual ~Exception() throw() {}
  virtual const Char8 *what() const throw() = 0;

  template <typename E>
  static Void Throw(const E &e);
};

#if PLATFORM_COMPILER_EXCEPTIONS
template<typename E>
Void Exception::Throw(const E &e) { throw e; }
# define CShift_LWF_Exception_try try
# define CShift_LWF_Exception_catch(e) catch (e)
#else // !PLATFORM_COMPILER_EXCEPTIONS
template<typename E>
Void Exception::Throw(const E &) { }
# define CShift_LWF_Exception_try
# define CShift_LWF_Exception_catch(e) if(false)
#endif // !PLATFORM_COMPILER_EXCEPTIONS

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_EXCEPTION_H
