#ifndef CSHIFT_MULTITASKING_THREAD_RW_MUTEX_H
#define CSHIFT_MULTITASKING_THREAD_RW_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread.h"
#include "Multitasking/Thread/Mutex/Synch.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Recursive/Timed/Mutex/State.h"
#include "Platform/OS/Independent/Multitasking/Timed/Mutex/Memory/State.h"
#include "Multitasking/RW/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Thread::RW::Mutex :
    Multitasking::RW::Mutex<
        Multitasking::Thread::Mutex::Synch,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State,
          Multitasking::Thread::Shared::Memory>,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking           ::Timed::Mutex::State,
          Multitasking::Thread::Shared::Memory> > {

  private: typedef
    Multitasking::RW::Mutex<
        Multitasking::Thread::Mutex::Synch,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State,
          Multitasking::Thread::Shared::Memory>,
        Platform::OS::Independent::Multitasking::Timed::Mutex::Memory::State<
          Platform::OS::Independent::Multitasking           ::Timed::Mutex::State,
          Multitasking::Thread::Shared::Memory> >
    Base;

  public: Mutex() : Base(Base::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_RW_MUTEX_H
