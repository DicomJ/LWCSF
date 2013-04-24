#ifndef CSHIFT_MULTITASKING_THREAD_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_THREAD_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread/Mutex.h"
#include "Multitasking/Mutex/Condition.h"
#include "Multitasking/Thread/Shared/Memory.h"
#include "Platform/OS/Multitasking/Thread/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Thread::Mutex::Condition : Thread::Mutex::Base::Condition {

  private: typedef Thread::Mutex::Base::Condition Base;
  public: Condition(Mutex &mutex)
    : Base(mutex, Multitasking::Thread::Shared::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_MUTEX_CONDITION_H
