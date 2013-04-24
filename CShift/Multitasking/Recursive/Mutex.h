#ifndef CSHIFT_MULTITASKING_RECURSIVE_MUTEX_H
#define CSHIFT_MULTITASKING_RECURSIVE_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Noncopyable.h"

namespace CShift {
namespace Multitasking {

template <typename Base> struct Mutex;
namespace Timed { template <typename Base> struct Mutex; } // namespace Timed

}} // namespace CShift::Multitasking

namespace CShift {
namespace Multitasking {
namespace Recursive {

template <typename Base>
struct Mutex : protected Base {

  static const UInt Shared = Base::Shared;

  typedef typename Base::Memory Memory;

  friend struct CShift::Multitasking::Mutex<Base>;
  friend struct CShift::Multitasking::Timed::Mutex<CShift::Multitasking::Mutex<Base> >;

  struct Lock;
  struct Try { struct Lock; };
  Bool operator == (const Mutex &mutex) const { return Base::operator == (mutex); }
  Bool operator != (const Mutex &mutex) const { return !(*this == mutex); }

  Mutex(const Memory &memory) : Base(memory) { }
};

template <typename Base>
struct Mutex<Base>::Lock : LWF::Traits::Noncopyable {
  Lock(Mutex &mutex) : mutex(mutex) { mutex.  lock(); }
  ~Lock()                           { mutex.unlock(); }
  protected: Mutex &mutex;
};

template <typename Base>
struct Mutex<Base>::Try::Lock : LWF::Traits::Noncopyable {
  Lock(Mutex &mutex) : mutex(mutex), locked(mutex.tryLock()) { }
  ~Lock() { if (locked) { mutex.unlock(); } }
  operator Bool () const { return locked; }
  protected: Mutex &mutex;
  private: Bool locked;
};

}}} // namespace CShift::Multitasking::Recursive

#endif // CSHIFT_MULTITASKING_RECURSIVE_MUTEX_H
