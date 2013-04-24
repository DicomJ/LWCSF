#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Thread.h"
#include "Platform/OS/Multitasking/Mutex.h"
#include "Platform/OS/API/Synch/Critical/Section.h"
#include "Multitasking/Thread/Shared/Memory.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

namespace Traits {
namespace Thread {

class Mutex : Platform::OS::API::Synch::Critical::Section {

  typedef Platform::OS::API::Synch::Critical::Section Base; public:
  typedef CShift::Multitasking::Thread::Shared::Memory Memory;
  static const UInt Shared = 0;

  Mutex(const Memory &) {}

  Void lock   () { Base::enter(); }
  Void unlock () { Base::leave(); }
  Bool tryLock() { return Base::tryEnter(); }

  Bool operator == (const Mutex &mutex) const {
    return Base::operator == (mutex);
  }
};

}} // Ttraits::Thread

struct Thread::Mutex : Platform::OS::Multitasking::Mutex<
                       Platform::OS::Multitasking::Traits::Thread::Mutex> {

  typedef Platform::OS::Multitasking::Mutex<
          Platform::OS::Multitasking::Traits::Thread::Mutex> Base; public:

  struct Condition;

  Mutex(const Memory &memory) : Base(memory) {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_THREAD_MUTEX_H
