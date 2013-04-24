#ifndef CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_SYNCH_H
#define CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_SYNCH_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process/Timed/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Process::Timed::Mutex::Synch : Process::Timed::Mutex::Base::Synch {

  private: typedef Process::Timed::Mutex::Base::Synch Base;
  public: Synch(const Text::String &name)
    : Base(*Process::Shared::Memory::create(
            Text::String("Process%Timed%Mutex%Synch%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_TIMED_MUTEX_SYNCH_H
