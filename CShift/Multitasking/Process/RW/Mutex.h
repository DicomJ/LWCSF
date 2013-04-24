#ifndef CSHIFT_MULTITASKING_PROCESS_RW_MUTEX_H
#define CSHIFT_MULTITASKING_PROCESS_RW_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process.h"
#include "Multitasking/Process/Mutex/Synch.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Recursive/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"
#include "Multitasking/RW/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Process::RW::Mutex :
    Multitasking::RW::Mutex<
        Multitasking::Process::Mutex::Synch,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State,
          Multitasking::Process::Shared::Memory>,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking           ::Timed::Mutex::State,
          Multitasking::Process::Shared::Memory> > {

  private: typedef
    Multitasking::RW::Mutex<
        Multitasking::Process::Mutex::Synch,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State,
          Multitasking::Process::Shared::Memory>,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking           ::Timed::Mutex::State,
          Multitasking::Process::Shared::Memory> >
    Base;

  public: Mutex(const Text::String &name)
      : Base(*Process::Shared::Memory::create(
              Text::String("Process%RW%Mutex%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_RW_MUTEX_H
