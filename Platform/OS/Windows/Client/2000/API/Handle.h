#ifndef CSHIFT_PLATFORM_OS_API_HANDLE_H
#define CSHIFT_PLATFORM_OS_API_HANDLE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Debug/Assert.h"
#include "Platform/OS/API/Result.h"

#include <WinDef.h>

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

template <UInt invalid>
struct Handle {

  typedef HANDLE Type;

  struct Exception { Exception(const Handle &) {} };

  Handle(Type handle_) : handle(Type(invalid)) { *this = handle_; }
  ~Handle() { detach(); }

  Void detach () {
    if (*this) { CloseHandle(handle); handle = Type(invalid); }
  }

  operator Bool() const { return handle != Type(invalid); }

  Bool operator == (const Handle &handle) const {
    return this->handle == handle.handle;
  }

  protected: Handle() : handle(Type(invalid)) {}
  Handle& operator = (Type handle) {
    LWF::Debug::Assert(Type(invalid) == this->handle,
                       "The handler reinitialization attemp detected. Current handler won't closed");
    (Result)(Type(invalid) != (this->handle = handle));
    return *this;
  }

  protected: operator Type () const { return handle; }

  private: Type handle;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_HANDLE_H
