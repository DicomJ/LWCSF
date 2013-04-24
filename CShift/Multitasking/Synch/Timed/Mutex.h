#ifndef CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace Multitasking {
namespace Synch {
namespace Timed {

template <typename Synch, typename State>
struct Mutex {

  typedef typename Synch::Mutex::Condition::Time Time;
  typedef typename Synch::Memory Memory;

  static const UInt Shared = Synch::Shared + State::Shared;

  class Condition;

  Void unlock() {
    typename Synch::Lock lock(synch); state = True;
    lock.notify(synch);
  }

  Void lock() {
    typename Synch::Lock lock(synch);
    while (!state) { lock.wait(synch); }
    state = False;
  }

  Bool tryLock() {
    typename Synch::Lock lock(synch);
    return state ? (state = False), True: False;
  }

  Bool timedLock(const Time &time) {
    typename Synch::Lock lock(synch);
    while (!state && lock.wait(synch).till(time)) {}
    return state ? (state = False), True: False;
  }

  Bool operator == (const Mutex &mutex) const {
    return synch.Synch::Mutex::operator == (mutex.synch);
  }

  Mutex(const Memory &memory) : synch(memory), state(memory) {}

  protected: operator typename Synch::Mutex & () { return synch; }

  protected: Synch synch;
  protected: State state;
};

}}}} // namespace CShift::Multitasking::Synch::Timed

#endif // CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_H
