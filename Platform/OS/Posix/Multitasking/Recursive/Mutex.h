#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_RECURSIVE_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_RECURSIVE_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Thread/Mutex.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {
namespace Recursive {

template <typename Memory_>
struct Mutex : Platform::OS::API::Thread::Mutex<Memory_> {

  public : typedef Memory_ Memory;
  private: typedef Platform::OS::API::Thread::Mutex<Memory> Base;
  public : typedef typename Base::Attribute Attribute;

  Mutex(const Memory &memory, const Attribute &attribute)
    : Base(memory, attribute) {}

  Void lock()     { Base::lock(); }
  Void unlock()   { Base::unlock(); }
  Bool tryLock()  { return Base::tryLock(); }

  Bool operator == (const Mutex &mutex) const {
    return Base::operator == (mutex);
  }
};

}}}}} // namespace CShift::Platform::OS::Multitasking::Recursive

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_RECURSIVE_MUTEX_H

