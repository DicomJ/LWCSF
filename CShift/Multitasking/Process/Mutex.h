#ifndef CSHIFT_MULTITASKING_PROCESS_MUTEX_H
#define CSHIFT_MULTITASKING_PROCESS_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Process/Shared/Memory.h"
#include "Platform/OS/Multitasking/Process/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Process::Mutex : Multitasking::Mutex<
                       Platform::OS::Multitasking::Process::Mutex> {

  private: typedef Multitasking::Mutex<
                   Platform::OS::Multitasking::Process::Mutex> Base; public:

  Mutex(const Text::String &name)
    : Base(*Process::Shared::Memory::create(
            Text::String("Process%Mutex%") + name, Base::Shared)) {}

  struct Condition;
  struct Synch;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_MUTEX_H
