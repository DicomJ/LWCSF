#ifndef CSHIFT_MULTITASKING_PROCESS_MUTEX_SYNCH_H
#define CSHIFT_MULTITASKING_PROCESS_MUTEX_SYNCH_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process/Mutex/Condition.h"
#include "Multitasking/Mutex/Synch.h"

namespace CShift {
namespace Multitasking {

struct Process::Mutex::Synch : Process::Mutex::Base::Synch {
  private: typedef Process::Mutex::Base::Synch Base;
  public : typedef Base::Memory Memory;
  public : Synch(const Text::String &name)
    : Base(*Process::Shared::Memory::create(
            Text::String("Process%Mutex%Synch%") + name, Base::Shared)) {}
  public : Synch(const Memory &memory) : Base(memory) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_MUTEX_SYNCH_H
