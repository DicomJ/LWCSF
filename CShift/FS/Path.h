#ifndef CSHIFT_FS_PATH_H
#define CSHIFT_FS_PATH_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/Path.h"

#include "Text/String.h"

namespace CShift {
namespace FS {

struct Path : Platform::OS::FS::Path {
  Path(const Text::String &path) : Platform::OS::FS::Path(path) {}
};

}} // namespace CShift::FS

#endif // CSHIFT_FS_PATH_H
