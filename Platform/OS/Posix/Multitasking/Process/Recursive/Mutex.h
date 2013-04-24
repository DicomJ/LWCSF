#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Process.h"
#include "Platform/OS/Multitasking/Recursive/Mutex.h"
#include "Multitasking/Process/Shared/Memory.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Process::Recursive::Mutex
    : Platform::OS::Multitasking::Recursive::Mutex<
      CShift::Multitasking::Process::Shared::Memory> {

  private: typedef Platform::OS::Multitasking::Recursive::Mutex<
                   CShift::Multitasking::Process::Shared::Memory> Base;

  public: Mutex(const typename Base::Memory &memory)
    : Base(memory, typename Base::Attribute().shared(True).
                   type(Base::Attribute::Mutex::Type::Recursive)) {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H

