#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_MODE_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_MODE_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Independent/FS/Object/Permition.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct Object::Permition::Mode {
  Mode(const Permition &user  = Permition::None,
       const Permition &group = Permition::None,
       const Permition &other = Permition::None)
    : user(user), group(group), other(other) {}

  Permition user;
  Permition group;
  Permition other;
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_PERMITION_MODE_H
