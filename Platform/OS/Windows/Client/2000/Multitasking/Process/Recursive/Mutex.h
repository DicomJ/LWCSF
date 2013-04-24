#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Synch/Mutex.h"
#include "Platform/OS/Multitasking/Process.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Process::Recursive::Mutex : Platform::OS::API::Synch::Mutex {

  typedef Platform::OS::API::Synch::Mutex Base; public:
  typedef CShift::Multitasking::Process::Shared::Memory Memory;
  static const UInt Shared = 0;

  Mutex(const Memory &memory) : Base(static_cast<const Text::String &>(memory)) {}

  Void lock()     { Base::wait(); }
  Void unlock()   { Base::release(); }
  Bool tryLock()  { return Base::wait(0); }

  Bool operator == (const Mutex &mutex) const {
    return Base::operator == (mutex);
  }
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H

