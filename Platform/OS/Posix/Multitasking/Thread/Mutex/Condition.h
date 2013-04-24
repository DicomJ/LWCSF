#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Mutex/Condition.h"
#include "Platform/OS/Multitasking/Thread/Mutex.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Thread::Mutex::Condition : Mutex::Base::Condition {

  private: typedef Mutex::Base::Condition Base;

  public: Condition(Mutex &mutex, const typename Mutex::Memory &memory)
    : Base(mutex, memory, typename Base::Attribute().shared(False)) {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_CONDITION_H


