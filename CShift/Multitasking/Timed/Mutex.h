#ifndef CSHIFT_MULTITASKING_TIMED_MUTEX_H
#define CSHIFT_MULTITASKING_TIMED_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Recursive/Timed/Mutex.h"
#include "LWF/Debug/Assert.h"

namespace CShift {
namespace Multitasking {
namespace Timed {

template <typename Base>
struct Mutex : Recursive::Timed::Mutex<Base> {

  struct Timed { struct Lock; };

  Mutex(const typename Base::Memory &memory) : Recursive::Timed::Mutex<Base>(memory) {}
};

template <typename Base>
struct Mutex<Base>::Timed::Lock : Recursive::Timed::Mutex<Base>::Timed::Lock {

  struct Unlock;

  Lock(Mutex &mutex, const typename Base::Time &time)
    : Recursive::Timed::Mutex<Base>::Timed::Lock(mutex, time) {}

  typename Base::Condition::Wait wait(typename Base::Condition &condition) {
    LWF::Debug::Assert(*this, "The mutex isn't locked ");
    return typename Base::Condition::Wait(condition, this->mutex);
  }
  typename Base::Condition::Notify notify(typename Base::Condition &condition) {
    LWF::Debug::Assert(*this, "The mutex isn't locked");
    return typename Base::Condition::Notify(condition, this->mutex);
  }
};

template <typename Base>
struct Mutex<Base>::Timed::Lock::Unlock {
  Unlock(Lock &lock) : lock(lock) {
    LWF::Debug::Assert(lock, "The mutex isn't locked ");
    lock.mutex.unlock();
  } ~Unlock() { lock.mutex.lock(); }
  private: Lock &lock;
};

}}} // namespace CShift::Multitasking::Timed

#endif // CSHIFT_MULTITASKING_TIMED_MUTEX_H
