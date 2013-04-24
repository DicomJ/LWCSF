#ifndef CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_STATE_H
#define CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_STATE_H

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

struct State {
  State() : unlocked(True) {}
  State &operator = (Bool unlock) { this->unlocked = unlock; return *this; }
  operator Bool () const { return unlocked; }
  private: Bool unlocked;
};

}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Timed::Mutex

#endif // CSHIFT_PLARFORM_OS_INDEPENDENT_MULTITASKING_TIMED_MUTEX_STATE_H
