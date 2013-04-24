#ifndef CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_MEMORY_STATE_H
#define CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_MEMORY_STATE_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace Multitasking {
namespace Timed {
namespace Mutex {
namespace Memory {

template <typename Substate, typename Memory>
struct State {
  static const UInt Shared = LWF::Type<Substate>::size;

  State(const Memory &memory) : state(memory) {
    if (null == state) { state = new (state.allocator()) Substate; }
  }
  State &operator = (Bool unlock) { *state = unlock; return *this; }
  operator Bool () const { return *state; }

  private: typename Memory::template Object<Substate> state;
};

}}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Timed::Mutex::Memory

#endif // CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_MEMORY_STATE_H
