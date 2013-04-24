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

  Void start(CShift::Multitasking::Runnable &runnable) {
    Base::create(platformStartRoutine, &runnable);
  }

  Void join() { Base::wait(); }
  Void detach() { Base::detach(); }

  typedef Base::Id Id;
  Id id() const { return Base::id(); }

  struct Max { static Int priority() { return Base::Idle; } };
  struct Min { static Int priority() { return Base::Critical; } };
  Int priority() const { return Base::priority(); }
  Void priority(Int priority) { Base::priority(priority); }

  static Void yield() { Sleep(0); }
  static Void sleep(const Time &time) { /*TODO: Sleep(time); */}

  protected: typedef Base::Self Self;
  protected: Self self() { return Base::current(); }
  protected: Thread(Self self) : Base(self) {}

  protected: Thread() {}

  private: static typename Base::Routine::Return
  PLATFORM_OS_API_CONVENTION platformStartRoutine(Void *parameter) {
    ((CShift::Multitasking::Runnable *)parameter)->run();
    return 0;
  }
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_H
