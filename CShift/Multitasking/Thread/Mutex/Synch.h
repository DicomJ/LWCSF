#ifndef CSHIFT_MULTITASKING_THREAD_MUTEX_SYNCH_H
#define CSHIFT_MULTITASKING_THREAD_MUTEX_SYNCH_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread/Mutex/Condition.h"
#include "Multitasking/Mutex/Synch.h"

namespace CShift {
namespace Multitasking {

struct Thread::Mutex::Synch : Thread::Mutex::Base::Synch {
  private: typedef Thread::Mutex::Base::Synch Base;
  public : typedef Base::Memory Memory;
  public : Synch() : Base(Memory()) {}
  public : Synch(const Memory &memory) : Base(memory) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_MUTEX_SYNCH_H
