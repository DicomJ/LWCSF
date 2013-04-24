#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Runnable.h"

#include "Platform/OS/Multitasking/Clock/Time.h"
#include "Platform/OS/API/Thread.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

class Thread : Platform::OS::API::Thread {
  typedef Platform::OS::API::Thread Base; public:

  struct Mutex;
  struct Recursive { struct Mutex; };

  typedef Platform::OS::Multitasking::Clock::Time Time;

  typedef Base::Self Self;
  static Self self() { return Base::self(); }
  Thread(Self self) : Base(self) {}

  Thread() {}

  Void start(CShift::Multitasking::Runnable &runnable) {
    Base::create(platformStartRoutine, &runnable, Base::Attribute().joinable(True));
  }

  Void join() { Base::join(); }
  Void detach() { Base::detach(); }

  typedef Base::Id Id;
  Id id() const { return Base::id(); }

  struct Max { static Int priority() { return Base::Max::priority(); } };
  struct Min { static Int priority() { return Base::Min::priority(); } };
  Int priority() const { return Base::priority(); }
  Void priority(Int priority) { Base::priority(priority); }

  static Void yield() { Base::yield(); }
  static Void sleep(const Time &time) { Base::sleep(time); }

  private: static Void *
  /*PLATFORM_OS_API_CONVENTION */platformStartRoutine(Void *parameter) {
    ((CShift::Multitasking::Runnable *)parameter)->run();
    return 0;
  }
};

}}}} // namespace CShifе::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_H
