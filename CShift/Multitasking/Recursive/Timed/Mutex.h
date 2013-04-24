#ifndef CSHIFT_MULTITASKING_RECURSIVE_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_RECURSIVE_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"

namespace CShift {
namespace Multitasking {
namespace Recursive {
namespace Timed {

template <typename Base>
struct Mutex : Base {
  struct Timed { struct Lock; };

  Mutex(const typename Base::Memory &memory) : Base(memory) {}
};

template <typename Base>
struct Mutex<Base>::Timed::Lock {

  Lock(Mutex &mutex, const typename Base::Time &time)
    : mutex(mutex), locked(mutex.timedLock(time)) {}
  ~Lock() { if (locked) { mutex.unlock(); } }
  operator Bool() const { return locked; }
  protected: Mutex &mutex;
  private: Bool locked;
};

}}}} // namespace CShift::Multitasking::Recursive::Timed

#endif // CSHIFT_MULTITASKING_RECURSIVE_TIMED_MUTEX_H
