#ifndef CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_H
#define CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Synch/Object.h"
#include "Platform/OS/API/Security/Attributes.h"
#include "Platform/OS/API/String.h"
#include "Platform/OS/API/Result.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Synch {

struct Event : Synch::Object<> {

  template <typename Mutex> struct Condition;

  Event(Bool initiallySignalized = False, Bool manualReset = False,
        Security::Attributes::Optional::Ptr securityAttributes = null,
        const String &name = String() )
    : Synch::Object<>(CreateEvent(
        Security::Attributes::Optional::ptr(securityAttributes),
        manualReset, initiallySignalized, Optional::lpctstr(name))) {
  }
  Void set  () { (Result)SetEvent  (*this); }
  Void pulse() { (Result)PulseEvent(*this); }
  Void reset() { (Result)ResetEvent(*this); }
};

}}}}} // namespace CShift::Platform::OS::API::Synch

#endif // CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_H
