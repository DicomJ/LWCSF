#ifndef CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process/Timed/Mutex.h"
#include "Multitasking/Process/Shared/Memory.h"
#include "Multitasking/Synch/Timed/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Process::Timed::Mutex::Condition : Process::Timed::Mutex::Base::Condition {

  private: typedef Process::Timed::Mutex::Base::Condition Base;
  public: Condition(Mutex &mutex, const Text::String &name)
    : Base(mutex, *Process::Shared::Memory::create(
            Text::String("Process%Timed%Mutex%Condition%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_CONDITION_H
