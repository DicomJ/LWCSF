#ifndef CSHIFT_MULTITASKING_MUTEX_H
#define CSHIFT_MULTITASKING_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Recursive/Mutex.h"
#include "LWF/Debug/Assert.h"

namespace CShift {
namespace Multitasking {

template <typename Base>
struct Mutex : Recursive::Mutex<Base> {
  struct Lock;
  struct Try { struct Lock; };
  struct Condition;
  struct Synch;

  Mutex(const typename Base::Memory &memory) : Recursive::Mutex<Base>(memory) { }
};

template <typename Base>
struct Mutex<Base>::Lock : Recursive::Mutex<Base>::Lock {
  struct Unlock;
  Lock(Mutex &mutex) : Recursive::Mutex<Base>::Lock(mutex) {}
  typename Condition::Wait wait(Condition &condition) {
    return typename Condition::Wait(condition, this->mutex);
  }
  typename Condition::Notify notify(Condition &condition) {
    return typename Condition::Notify(condition, this->mutex);
  }
};

template <typename Base>
struct Mutex<Base>::Lock::Unlock {
  Unlock(Lock &lock_) : lock(lock_) { lock.mutex.unlock(); }
  ~Unlock()                         { lock.mutex.  lock(); }
  private: Lock &lock;
};

template <typename Base>
struct Mutex<Base>::Try::Lock : Recursive::Mutex<Base>::Try::Lock {
  struct Unlock;
  Lock(Mutex &mutex) : Recursive::Mutex<Base>::Try::Lock(mutex) {}
  typename Condition::Wait wait(Condition &condition) {
    LWF::Debug::Assert(*this, "The mutex isn't locked");
    return typename Condition::Wait(condition, this->mutex);
  }
  typename Condition::Notify notify(Condition &condition) {
    LWF::Debug::Assert(*this, "The mutex isn't locked");
    return typename Condition::Notify(condition, this->mutex);
  }
};

template <typename Base>
struct Mutex<Base>::Try::Lock::Unlock {
  Unlock(Lock &lock) : lock(lock) {
    LWF::Debug::Assert(lock, "The mutex isn't locked");
    lock.mutex.unlock();
  } ~Unlock() { lock.mutex.lock(); }
  private: Lock &lock;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_MUTEX_H
