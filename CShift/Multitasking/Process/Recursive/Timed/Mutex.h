#ifndef CSHIFT_MULTITASKING_PROCESS_RECURSIVE_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_PROCESS_RECURSIVE_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Recursive/Timed/Mutex.h"
#include "Multitasking/Recursive/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex.h"
#include "Multitasking/Process/Mutex/Synch.h"
#include "Multitasking/Current/ProcessAndThread.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"
#include "Platform/OS/Independent/Multitasking/Recursive/Timed/Mutex/Space/State.h"

namespace CShift {
namespace Multitasking {

struct Process::Recursive::Timed::Mutex :
    Multitasking::Recursive::Timed::Mutex<
    Multitasking::Recursive::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Process::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::Space<
          Multitasking::Current::ProcessAndThread>::State,
        Multitasking::Process::Shared::Memory> > > > {

  private:  typedef
  Multitasking::Recursive::Timed::Mutex<
  Multitasking::Recursive::Mutex<
  Multitasking::Synch::Timed::Mutex<
    Multitasking::Process::Mutex::Synch,
    Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
      Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::Space<
        Multitasking::Current::ProcessAndThread>::State,
      Multitasking::Process::Shared::Memory> > > > Base;

  public: Mutex(const Text::String &name)
    : Base(*Process::Shared::Memory::create(
            Text::String("Process%Recursive%Timed%Mutex%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_RECURSIVE_TIMED_MUTEX_H
