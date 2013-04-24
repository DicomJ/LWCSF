#ifndef CSHIFT_MULTITASKING_THREAD_MUTEX_H
#define CSHIFT_MULTITASKING_THREAD_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Thread/Shared/Memory.h"
#include "Platform/OS/Multitasking/Thread/Mutex.h"

namespace CShift {
namespace Multitasking {

struct Thread::Mutex : Multitasking::Mutex<
                       Platform::OS::Multitasking::Thread::Mutex> {

  private: typedef Multitasking::Mutex<
                   Platform::OS::Multitasking::Thread::Mutex> Base; public:

  Mutex() : Base(Multitasking::Thread::Shared::Memory()) {}

  struct Condition;
  struct Synch;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_MUTEX_H
