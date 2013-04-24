#ifndef CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_STATE_H
#define CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_STATE_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace Multitasking {
namespace Recursive {
namespace Timed {
namespace Mutex {

struct State {
  State() : locked(0) { }
  State &operator = (Bool unlock) {
    if (unlock) { --locked; } else { ++locked; } return *this;
  }
  operator Bool () const { return 0 == locked; }
  private: UInt locked;
};

}}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Recursive::Timed::Mutex

#endif // CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_STATE_H
