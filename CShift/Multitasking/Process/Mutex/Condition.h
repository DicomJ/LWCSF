#ifndef CSHIFT_MULTITASKING_PROCESS_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_PROCESS_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process/Mutex.h"
#include "Multitasking/Mutex/Condition.h"
#include "Multitasking/Process/Shared/Memory.h"
#include "Platform/OS/Multitasking/Process/Mutex/Condition.h"

namespace CShift {
namespace Multitasking {

struct Process::Mutex::Condition : Process::Mutex::Base::Condition {

  private: typedef Process::Mutex::Base::Condition Base;
  public: Condition(Mutex &mutex, const Text::String &name)
    : Base(mutex, *Process::Shared::Memory::create(
            Text::String("Process%Mutex%Condition%") + name, Base::Shared)) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_MUTEX_CONDITION_H
