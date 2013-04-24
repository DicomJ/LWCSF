#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_ACCESS_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_ACCESS_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "LWF/Flags.h"
#include "Platform/OS/Independent/FS/Object.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct Object::Access : LWF::Flags {

  enum {
    None      = 0,
    Write     = 2,
    Read      = 4,
    ReadWrite = Read + Write,
    All       = ReadWrite
  };

  Bool canWrite     () const { return *this & Write    ; }
  Bool canRead      () const { return *this & Read     ; }
  Bool canReadWrite () const { return *this & ReadWrite; }

  Bool readOnly      () const { return Read      == *this; }
  Bool writeOnly     () const { return Write     == *this; }
  Bool readWriteOnly () const { return ReadWrite == *this; }

  Access(LWF::Flags::Type access) : LWF::Flags(access) {}
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_OBJECT_ACCESS_H
