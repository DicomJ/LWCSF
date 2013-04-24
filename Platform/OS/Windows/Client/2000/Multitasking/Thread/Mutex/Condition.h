#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Clock/Time.h"
#include "Platform/OS/Multitasking/Thread/Mutex.h"
#include "Platform/OS/API/Synch/Event/Condition.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Thread::Mutex::Condition : Platform::OS::API::Synch::Event::Condition<
                                  Platform::OS::Multitasking::Thread::Mutex> {

  private: typedef Platform::OS::API::Synch::Event::Condition<
                   Platform::OS::Multitasking::Thread::Mutex> Base; public:

  Condition(Mutex &/*mutex*/,
            const typename Thread::Mutex::Memory &memory) : Base(memory) {}

  Void signal()     { Base::signal(); }
  Void broadcast()  { Base::broadcast(); }

  void wait(Mutex &mutex) { Base::wait(mutex); }

  Bool wait(Mutex &mutex, const Clock::Time &time) {
    return Base::wait(mutex, time);
  }
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H
