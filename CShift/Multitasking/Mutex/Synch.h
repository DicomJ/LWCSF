#ifndef CSHIFT_MULTITASKING_MUTEX_SYNCH_H
#define CSHIFT_MULTITASKING_MUTEX_SYNCH_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Mutex.h"

namespace CShift {
namespace Multitasking {

template <typename Base>
struct Mutex<Base>::Synch : Mutex, Mutex::Condition {

  typedef typename Base::Memory Memory;

  Synch(const Memory &memory)
    : Mutex(memory), Mutex::Condition((Mutex &)*this, memory) {}

  static const UInt Shared = Mutex::Shared + Mutex::Condition::Shared;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_MUTEX_SYNCH_H
