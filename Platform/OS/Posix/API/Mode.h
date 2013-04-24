#ifndef CSHIFT_PLATFORM_OS_API_MODE_H
#define CSHIFT_PLATFORM_OS_API_MODE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Flags.h"

#include <sys/stat.h>

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct Mode : LWF::Flags {
  enum {
    UserRead        = S_IRUSR,
    UserWrite       = S_IWUSR,
    UserExecute     = S_IXUSR,

    UserReadWrite   = UserRead + UserWrite,
    UserAll         = UserReadWrite + UserExecute,

    GroupRead       = S_IRGRP,
    GroupWrite      = S_IWGRP,
    GroupExecute    = S_IXGRP,

    GroupReadWrite  = GroupRead + GroupWrite,
    GroupAll        = GroupReadWrite + GroupExecute,

    OtherRead       = S_IROTH,
    OtherWrite      = S_IWOTH,
    OtherExecute    = S_IXOTH,

    OtherReadWrite  = OtherRead + OtherWrite,
    OtherAll        = OtherReadWrite + OtherExecute,

    All             = UserAll + GroupAll + OtherAll,
    Default         = UserReadWrite + GroupReadWrite + OtherReadWrite
  };

  Mode(LWF::Flags::Type mode) : LWF::Flags(mode) {}
};


}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_MODE_H
