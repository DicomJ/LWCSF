#ifndef CSHIFT_PLATFORM_OS_API_THREAD_H
#define CSHIFT_PLATFORM_OS_API_THREAD_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Synch/Object.h"
#include "Platform/OS/API/ProcessThreads.h"
#include "Platform/OS/API/Security/Attributes.h"
//#include "Platform/OS/API/String.h"
//#include "Platform/OS/API/Result.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct Thread : Synch::Object<> {

  private: typedef Synch::Object<> Base; public:

  enum Priority {
    #include "Platform/OS/API/Thread/Priority.h"
    Idle        = THREAD_PRIORITY_IDLE,
    Lowest      = THREAD_PRIORITY_LOWEST,
    BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
    Normal      = THREAD_PRIORITY_NORMAL,
    AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
    Highest     = THREAD_PRIORITY_HIGHEST,
    Critical    = THREAD_PRIORITY_TIME_CRITICAL
  };

  typedef typename Base::Type Self;
  typedef DWORD Id;
  struct Routine {
    typedef LPTHREAD_START_ROUTINE Start;
    typedef DWORD Return;
  };

  static Self current() { return GetCurrentThread(); }
  Thread(Self self) : Base(self) {}
  Thread() {}

  Void create(Routine::Start startAddress,
              Void *parameter = 0,
              UInt creationFlags = 0,
              UInt stackSize = 0,
              Security::Attributes::Optional::Ptr securityAttributes = null) {
    Base::operator = (
        CreateThread( Security::Attributes::Optional::ptr(securityAttributes),
                      stackSize, startAddress, parameter, creationFlags, NULL));
  }

  Id id() const {
    Id id = GetThreadId(*this); return Result(id != 0), id;
  }

  Int priority() const {
    Int priority = GetThreadPriority(*this);
    return Result(priority != THREAD_PRIORITY_ERROR_RETURN), priority;
  }
  Void priority(Int priority) { (Result)SetThreadPriority(*this, priority); }
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_THREAD_H
