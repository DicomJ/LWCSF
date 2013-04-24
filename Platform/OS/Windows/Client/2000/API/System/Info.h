#ifndef CSHIFT_PLATFORM_OS_API_SYSTEM_INFO_H
#define CSHIFT_PLATFORM_OS_API_SYSTEM_INFO_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Base.h"

#include "LWF/Type.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace System {

struct Info : private SYSTEM_INFO {

  UInt pageSize() const { return SYSTEM_INFO::dwPageSize; }

  static const Info &instance() { static const Info info; return info;}
  private: Info() { GetSystemInfo(this); }
};

}}}}} // namespace CShift::Platform::OS::API::System

#endif // CSHIFT_PLATFORM_OS_API_SYSTEM_INFO_H
