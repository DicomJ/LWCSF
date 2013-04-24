#ifndef CSHIFT_MULTITASKING_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Timed/Mutex.h"
#include "Multitasking/Clock/Time.h"

namespace CShift {
namespace Multitasking {

template <typename Base>
struct Mutex<Base>::Condition : protected Base::Condition {

  typedef Clock::Time Time;

  static const UInt Shared = Base::Condition::Shared;

  class Wait;
  class Notify;
  Condition (Mutex &mutex, const typename Base::Memory &memory)
    : Base::Condition(mutex, memory), mutex(mutex) {}

  protected: Void signal() { Base::Condition::signal(); }
  protected: Void broadcast() { Base::Condition::broadcast(); }

  protected: Void wait() { Base::Condition::wait(mutex); }
  protected: Bool wait(const Time &time) {
    return Base::Condition::wait(mutex, time);
  }
  private: Mutex &mutex;
};

template <typename Base>
class Mutex<Base>::Condition::Wait {
  friend struct Mutex::Lock;
  friend struct Mutex::Try::Lock;
  friend struct CShift::Multitasking::Timed::Mutex<Mutex>::Timed::Lock;
  Wait(Condition &condition_, Recursive::Mutex<Base> &mutex)
    : condition(condition_), infinity(True) {
      LWF::Debug::Assert(mutex == condition.mutex,
          "An attemp to wait on another mutex than a condition was created for");
  }
  public: Bool till(const Time &time) {
    return (infinity = False), condition.wait(time);
  }
  public: ~Wait() { if (infinity) { condition.wait(); } }

  private: Condition &condition;
  private: Bool infinity;
};

template <typename Base>
class Mutex<Base>::Condition::Notify {
  friend struct Mutex::Lock;
  friend struct Mutex::Try::Lock;
  friend struct CShift::Multitasking::Timed::Mutex<Mutex>::Timed::Lock;
  Notify(Condition &condition_, Recursive::Mutex<Base> &mutex)
    : condition(condition_), single(True) {
      LWF::Debug::Assert(mutex == condition.mutex,
          "An attemp to notify on another mutex than a condition was created for");
  }
  public: Void all() { single = False; }
  public: ~Notify() { if (single) { condition.signal(); } else { condition.broadcast(); } }

  private: Condition &condition;
  private: Bool single;
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_MUTEX_CONDITION_H
