#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Independent/FS/Object/Access.h"
#include "LWF/Debug/Assert.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct Object::Permition : Platform::OS::Independent::FS::Object::Access {

  struct Mode;

  enum {
    Execute = 1,
    All     = Access::ReadWrite + Execute
  };

  Bool canExecute () const { return *this & Execute; }
  Bool executeOnly() const { return Execute == *this; }

  Permition(Access::Type permition) : Access(permition) {
    LWF::Debug::Assert((permition | All) == All);
  }
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_H
