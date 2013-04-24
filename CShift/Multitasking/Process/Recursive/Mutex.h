#ifndef CSHIFT_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H
#define CSHIFT_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process.h"
#include "Multitasking/Recursive/Mutex.h"
#include "Multitasking/Process/Shared/Memory.h"
#include "Platform/OS/Multitasking/Process/Recursive/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Process::Recursive::Mutex
    : Multitasking::Recursive::Mutex<
      Platform::OS::Multitasking::Process::Recursive::Mutex> {

  private: typedef Multitasking::Recursive::Mutex<
                   Platform::OS::Multitasking::Process::Recursive::Mutex> Base;
  public: Mutex(const Text::String &name)
    : Base(*Process::Shared::Memory::create(
            Text::String("Process%Recursive%Mutex%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_RECURSIVE_MUTEX_H
