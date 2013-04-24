#ifndef CSHIFT_PLATFORM_OS_API_SYNCH_MUTEX_H
#define CSHIFT_PLATFORM_OS_API_SYNCH_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Synch/Object.h"
#include "Platform/OS/API/String.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Synch {

struct Mutex : Synch::Object<> {

  Mutex(const String &name = String(),
        Bool initiallyOwned = False,
        Security::Attributes::Optional::Ptr securityAttributes = null)
    : Synch::Object<>(CreateMutex(
        Security::Attributes::Optional::ptr(securityAttributes),
        initiallyOwned, Optional::lpctstr(name))) {
  }

  Void release() { (Result)ReleaseMutex(*this); }
};

}}}}} // namespace CShift::Platform::OS::API::Synch

#endif // CSHIFT_PLATFORM_OS_API_SYNCH_MUTEX_H
