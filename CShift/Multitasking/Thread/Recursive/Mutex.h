#ifndef CSHIFT_MULTITASKING_THREAD_RECURSIVE_MUTEX_H
#define CSHIFT_MULTITASKING_THREAD_RECURSIVE_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread.h"
#include "Multitasking/Recursive/Mutex.h"
#include "Multitasking/Thread/Shared/Memory.h"
#include "Platform/OS/Multitasking/Thread/Recursive/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Thread::Recursive::Mutex
    : Multitasking::Recursive::Mutex<
      Platform::OS::Multitasking::Thread::Recursive::Mutex> {

  private: typedef Multitasking::Recursive::Mutex<
                   Platform::OS::Multitasking::Thread::Recursive::Mutex> Base;
  public: Mutex() : Base(Multitasking::Thread::Shared::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_RECURSIVE_MUTEX_H
