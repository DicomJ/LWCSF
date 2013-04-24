#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_CONDITION_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Clock/Time.h"
#include "Platform/OS/Multitasking/Mutex.h"
#include "Platform/OS/API/Thread/Mutex/Condition.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

template<typename Memory>
struct Mutex<Memory>::Condition
    : private Platform::OS::API::Thread::Mutex<Memory>::Condition {

  private: typedef typename Platform::OS::API::Thread::Mutex<Memory>::Condition Base;
  public: typedef typename Base::Attribute Attribute;

  public: static const UInt Shared = Base::Shared;

  public: Condition(Mutex &, const Memory &memory, const Attribute &attribute)
    : Base(memory, attribute) {}

  Void signal()     { Base::signal(); }
  Void broadcast()  { Base::broadcast(); }

  void wait(Mutex &mutex) { Base::wait(mutex); }
  Bool wait(Mutex &mutex, const Clock::Time &time) {
    return Base::wait(mutex, time);
  }
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_CONDITION_H


