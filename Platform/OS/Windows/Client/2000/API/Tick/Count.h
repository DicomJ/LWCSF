#ifndef CSHIFT_PLATFORM_OS_API_TICK_COUNT_H
#define CSHIFT_PLATFORM_OS_API_TICK_COUNT_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Base.h"

#include "LWF/Integer.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Tick {

struct Count {
  private: typedef LWF::Signed  ::Integer<
    LWF::Type<DWORD>::size>::Type Int;
  private: typedef LWF::Unsigned::Integer<
    LWF::Type<DWORD>::size>::Type UInt; public:

  static Count now() { return GetTickCount(); }

  template <typename Synch>
  Bool wait(Synch &synch) {
    Int ms = *this - Tick::Count::now(); // DON'T wait more than DWORD_MAX / 2
    return ms < 0 ? False : synch.wait(DWORD(ms));
  }

  Count(UInt count_) : count(count_) {}
  operator UInt() const { return count; }

  private: Int operator - (const Count &tc) const {

    return Int(count) - Int(tc.count);
  }
  private: UInt count;
};

}}}}} // namespace CShift::Platform::OS::API::Tick

#endif // CSHIFT_PLATFORM_OS_API_TICK_COUNT_H
