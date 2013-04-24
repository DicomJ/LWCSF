#ifndef CSHIFT_PLATFORM_OS_API_SYNCH_OBJECT_H
#define CSHIFT_PLATFORM_OS_API_SYNCH_OBJECT_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Handle.h"
#include "Platform/OS/API/Synch.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Synch {

template <UInt invalid = UInt(NULL),
          typename Handle = Handle<invalid> >
struct Object : Handle {

  struct Exception : Handle::Exception {
    Exception(const Object &object) : Handle::Exception(object) {}
  };

  Bool wait(UInt ms) {
    DWORD dw = WaitForSingleObject(*this, ms);
    switch (dw) {
    case WAIT_OBJECT_0:
    case WAIT_ABANDONED: // Mutex wasn't released
      return True;
    case WAIT_FAILED:
      LWF::Exception::Throw(Exception(*this));
    case WAIT_TIMEOUT:
    default:
      return False;
    }
  }

  Void wait() { wait(INFINITE); }

  template <typename Timer>
  Bool wait(Timer &timer) { return /*timer.wait(*this);*/ False; }

  Object(typename Handle::Type handle) : Handle(handle) {}
  protected: Object() {}
  protected: Object& operator = (HANDLE handle) {
    Handle::operator = (handle); return *this;
  }
};

}}}}} // namespace CShift::Platform::OS::API::Synch

#endif // CSHIFT_PLATFORM_OS_API_SYNCH_OBJECT_H
