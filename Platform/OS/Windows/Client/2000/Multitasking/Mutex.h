#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Debug/Assert.h"
#include "Platform/OS/API/Synch/Event.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

template <typename Base>
struct Mutex : Base {

  typedef typename Base::Memory Memory;

  static const UInt Shared = Base::Shared + LWF::Type<Bool>::size;

  struct Exception : LWF::Exception {
    Exception(const Mutex &) {}
    virtual const Char8 *what() const throw() {
      return "Non-recursive mutex can't be locked twice "
              "event by the same thread";
    }
  };

  Mutex(const Memory &memory) : Base(memory), locked(memory) {
    if (null == locked) { locked = new (locked.allocator()) Bool(False); }
  }

  Void lock() { Base::lock(); lock_(); }
  Void unlock() { *locked = False; Base::unlock(); }
  Bool tryLock(){ return Base::tryLock(); lock_(); }

  Bool operator == (const Mutex &mutex) const {
    return Base::operator == (mutex);
  }

  private: Void lock_() {
    if (*locked) {
      LWF::Debug::Assert(!*locked, Exception(*this));
      Platform::OS::API::Synch::Event().wait();
    } else { *locked = True; }
  }
  private: typename Memory::template Object<Bool> locked;
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H
