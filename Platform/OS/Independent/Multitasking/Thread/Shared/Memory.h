#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_THREAD_SHARED_MEMORY_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_THREAD_SHARED_MEMORY_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Surrogate.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace Multitasking {
namespace Thread {
namespace Shared {

struct Memory {

  operator Bool() const { return False; } // Tells whether memory is initialized

  template <typename T> struct Block : private LWF::Traits::Surrogate<T> {

    Block(const Memory &) {}

    operator LWF::Weak::Ptr<T> () const { return const_cast<T *>(&**this); }
  };
};

}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Thread::Shared

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_THREAD_SHARED_MEMORY_H
