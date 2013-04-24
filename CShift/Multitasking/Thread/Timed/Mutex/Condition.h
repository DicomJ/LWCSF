#ifndef CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread/Timed/Mutex.h"
#include "Multitasking/Thread/Shared/Memory.h"
#include "Multitasking/Synch/Timed/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Thread::Timed::Mutex::Condition : Thread::Timed::Mutex::Base::Condition {

  private: typedef Thread::Timed::Mutex::Base::Condition Base;
  public: Condition(Mutex &mutex)
    : Base(mutex, Multitasking::Thread::Shared::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_CONDITION_H
