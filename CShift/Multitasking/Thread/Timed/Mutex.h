#ifndef CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Timed/Mutex.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex.h"
#include "Multitasking/Thread/Mutex/Synch.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"

namespace CShift {
namespace Multitasking {

struct Thread::Timed::Mutex
  : Multitasking::Timed::Mutex<
    Multitasking::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Thread::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Timed::Mutex::State,
        Multitasking::Thread::Shared::Memory> > > >  {

  private: typedef
    Multitasking::Timed::Mutex<
    Multitasking::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Thread::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Timed::Mutex::State,
        Multitasking::Thread::Shared::Memory> > > > Base;

  public: Mutex() : Base(Memory()) {}

  struct Condition;
  struct Synch;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_H
