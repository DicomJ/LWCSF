#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_RECURSIVE_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_RECURSIVE_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/Multitasking/Thread.h"
#include "Platform/OS/API/Synch/Critical/Section.h"
#include "Multitasking/Thread/Shared/Memory.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

class Thread::Recursive::Mutex : Platform::OS::API::Synch::Critical::Section {

  typedef Platform::OS::API::Synch::Critical::Section Base; public:
  typedef CShift::Multitasking::Thread::Shared::Memory Memory;

  struct Condition;

  Void lock()   { Base::enter(); }
  Void unlock() { Base::leave(); }
  Bool tryLock(){ return Base::tryEnter(); }

  Bool operator == (const Mutex &mutex) const { return Base::operator == (mutex); }

  Mutex(const Memory &) {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_RECURSIVE_MUTEX_H
