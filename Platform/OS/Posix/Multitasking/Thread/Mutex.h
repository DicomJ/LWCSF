#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Thread.h"
#include "Platform/OS/Multitasking/Mutex.h"
#include "Multitasking/Thread/Shared/Memory.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Thread::Mutex
    : Platform::OS::Multitasking::Mutex<
      CShift::Multitasking::Thread::Shared::Memory> {

  private: typedef Platform::OS::Multitasking::Mutex<
                   CShift::Multitasking::Thread::Shared::Memory> Base;

  public: Mutex(const typename Base::Memory &memory)
    : Base(memory, typename Base::Attribute().shared(False)) {}

  struct Condition;
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H
