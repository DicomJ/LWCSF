#ifndef CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_SPACE_STATE_H
#define CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_SPACE_STATE_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/Independent/Multitasking/Recursive/Timed/Mutex/State.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace Multitasking {
namespace Recursive {
namespace Timed {
namespace Mutex {

template <typename T>
struct Space {

  struct State : Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State {
    private: typedef T Space; public:
    State &operator = (Bool unlock) {
      Platform::OS::Independent::Multitasking::Recursive::Timed::Mutex::State &base = *this;
      if (!unlock && base) { id = Space().id(); } base = unlock;
      return *this;
    }
    operator Bool () const {
      const Timed::Mutex::State &base = *this;
      return (Bool)base || Space().id() == id;
    }
    private: typename Space::Id id;
  };
};

}}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Recursive::Timed::Mutex

#endif // CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_RECURSIVE_TIMED_MUTEX_SPACE_STATE_H
