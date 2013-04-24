#ifndef CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Timed/Mutex.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex.h"
#include "Multitasking/Process/Mutex/Synch.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"

namespace CShift {
namespace Multitasking {

struct Process::Timed::Mutex
  : Multitasking::Timed::Mutex<
    Multitasking::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Process::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Timed::Mutex::State,
        Multitasking::Process::Shared::Memory> > > >  {

  private: typedef
    Multitasking::Timed::Mutex<
    Multitasking::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Process::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Timed::Mutex::State,
        Multitasking::Process::Shared::Memory> > > > Base;

  public: Mutex(const Text::String &name)
      : Base(*Process::Shared::Memory::create(
              Text::String("Process%Timed%Mutex%") + name, Base::Shared)) {}

  struct Condition;
  struct Synch;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_H
