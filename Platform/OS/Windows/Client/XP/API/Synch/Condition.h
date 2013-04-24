#ifndef CSHIFT_PLATFORM_OS_WINDOWS_XP_API_SYNCH_CONDITION_H
#define CSHIFT_PLATFORM_OS_WINDOWS_XP_API_SYNCH_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/Multitasking/Clock/Time.h"
#include "Platform/OS/API/Synch.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Windows {
namespace XP {
namespace API {

struct Condition {

  Condition() { InitializeConditionVariable(&condition); }
  ~Condition() {}

  private: CONDITION_VARIABLE condition;
};

}}}}}} // namespace CShift::Platform::OS::XP::API::Synch

#endif // CSHIFT_PLATFORM_OS_WINDOWS_XP_API_SYNCH_CONDITION_H
