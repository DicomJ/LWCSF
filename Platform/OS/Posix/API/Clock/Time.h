#ifndef CSHIFT_PLATFORM_OS_API_CLOCK_TIME_H
#define CSHIFT_PLATFORM_OS_API_CLOCK_TIME_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include <time.h>

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

namespace Clock {

struct Time : private timespec {
  operator const timespec * () const { return this; }
};

}}}}} // namespace CShift::Platform::OS::API:Clock

#endif // CSHIFT_PLATFORM_OS_API_CLOCK_TIME_H
