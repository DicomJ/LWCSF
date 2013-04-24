#ifndef CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_SYNCH_H
#define CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_SYNCH_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread/Timed/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Thread::Timed::Mutex::Synch : Thread::Timed::Mutex::Base::Synch {

  private: typedef Thread::Timed::Mutex::Base::Synch Base;
  public: Synch() : Base(Base::Memory()) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_TIMED_MUTEX_SYNCH_H
