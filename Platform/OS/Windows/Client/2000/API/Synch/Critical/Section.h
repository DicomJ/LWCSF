#ifndef CSHIFT_PLATFORM_OS_API_SYNCH_CRITICAL_SECTION_H
#define CSHIFT_PLATFORM_OS_API_SYNCH_CRITICAL_SECTION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Synch.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Synch {
namespace Critical {

struct Section {

  Section() { InitializeCriticalSection(&section); }
  ~Section() { DeleteCriticalSection(&section); }

  Void enter() { EnterCriticalSection(&section); }
  Bool tryEnter() { return TryEnterCriticalSection(&section); }
  Void leave() { LeaveCriticalSection(&section); }

  Section(UInt count) { InitializeCriticalSectionAndSpinCount(&section, count); }
  Void spin(UInt count) { SetCriticalSectionSpinCount(&section, count); }

  Bool operator == (const Section &section) const { return this == &section; }

  private: CRITICAL_SECTION section;
};

}}}}}} // namespace CShift::Platform::OS::API::Critical::Synch::Critical

#endif // CSHIFT_PLATFORM_OS_API_SYNCH_CRITICAL_SECTION_H
