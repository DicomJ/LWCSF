#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Process.h"
#include "Platform/OS/Multitasking/Mutex.h"
#include "Platform/OS/API/Synch/Mutex.h"
#include "Multitasking/Process/Shared/Memory.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

namespace Traits {
namespace Process {

class Mutex : Platform::OS::API::Synch::Mutex {

  typedef Platform::OS::API::Synch::Mutex Base; public:
  typedef CShift::Multitasking::Process::Shared::Memory Memory;
  static const UInt Shared = 0;

  Mutex(const Memory &memory) : Base(static_cast<const Text::String &>(memory)) {}

  Void lock   () { Base::wait(); }
  Void unlock () { Base::release(); }
  Bool tryLock() { return Base::wait(0); }

  Bool operator == (const Mutex &mutex) const {
    return Base::operator == (mutex);
  }
};

}} // Ttraits::Process

struct Process::Mutex : Platform::OS::Multitasking::Mutex<
                       Platform::OS::Multitasking::Traits::Process::Mutex> {

  typedef Platform::OS::Multitasking::Mutex<
          Platform::OS::Multitasking::Traits::Process::Mutex> Base; public:

  struct Condition;

  Mutex(const Memory &memory) : Base(memory) {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_MUTEX_H
