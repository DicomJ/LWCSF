#ifndef CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_CONDITION_H
#define CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_CONDITION_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

namespace CShift {
namespace Multitasking {
namespace Synch {
namespace Timed {

template <typename Synch, typename State>
class Mutex<Synch, State>::Condition : Synch::Mutex::Condition {

  typedef typename Synch::Mutex::Condition Base; public:

  static const UInt Shared = Synch::Mutex::Condition::Shared;

  Condition(Mutex &mutex, const typename Synch::Mutex::Memory &memory)
    : Base(mutex, memory) {}

  Void signal() { Base::signal(); }
  Void broadcast() { Base::broadcast(); }

  Void wait(const Mutex &) { Base::wait(); }
  Bool wait(const Mutex &, const Time &time) { return Base::wait(time); }
};

}}}} // namespace CShift::Multitasking::Synch::Timed

#endif // CSHIFT_MULTITASKING_SYNCH_TIMED_MUTEX_CONDITION_H
