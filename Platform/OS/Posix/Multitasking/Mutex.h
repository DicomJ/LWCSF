#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Multitasking/Recursive/Mutex.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

template <typename Memory>
struct Mutex : Platform::OS::Multitasking::Recursive::Mutex<Memory> {

  private: typedef Platform::OS::Multitasking::Recursive::Mutex<Memory> Base; public:

  Mutex(const Memory &memory, const typename Base::Attribute &attribute)
    : Base(memory, attribute) {}

  struct Condition;
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_MUTEX_H
