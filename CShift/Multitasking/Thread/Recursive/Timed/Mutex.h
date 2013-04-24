#ifndef CSHIFT_MULTITASKING_THREAD_RECURSIVE_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_THREAD_RECURSIVE_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Recursive/Timed/Mutex.h"
#include "Multitasking/Recursive/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex.h"
#include "Multitasking/Thread/Mutex/Synch.h"
#include "Multitasking/Current/Thread.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"
#include "Platform/OS/Independent/Multitasking/Recursive/Timed/Mutex/Space/State.h"

namespace CShift {
namespace Multitasking {

struct Thread::Recursive::Timed::Mutex :
    Multitasking::Recursive::Timed::Mutex<
    Multitasking::Recursive::Mutex<
    Multitasking::Synch::Timed::Mutex<
      Multitasking::Thread::Mutex::Synch,
      Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
        Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::Space<
          Multitasking::Current::Thread>::State,
        Multitasking::Thread::Shared::Memory> > > > {

  private:  typedef
  Multitasking::Recursive::Timed::Mutex<
  Multitasking::Recursive::Mutex<
  Multitasking::Synch::Timed::Mutex<
    Multitasking::Thread::Mutex::Synch,
    Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
      Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::Space<
        Multitasking::Current::Thread>::State,
      Multitasking::Thread::Shared::Memory> > > > Base;

  public: Mutex() : Base(Base::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_RECURSIVE_TIMED_MUTEX_H
