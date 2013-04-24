#ifndef CSHIFT_PLATFORM_OS_API_SECURITY_ATTRIBUTES_H
#define CSHIFT_PLATFORM_OS_API_SECURITY_ATTRIBUTES_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Base.h"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Security {

struct Attributes : SECURITY_ATTRIBUTES {

  struct Optional {
    typedef LWF::Weak::Ptr<Attributes> Ptr;

    static LPSECURITY_ATTRIBUTES ptr(Ptr ptr) {
      return ptr != null ? &*ptr : NULL;
    }
  };
};

}}}}} // namespace CShift::Platform::OS::API::Security

#endif // CSHIFT_PLATFORM_OS_API_SECURITY_ATTRIBUTES_H
