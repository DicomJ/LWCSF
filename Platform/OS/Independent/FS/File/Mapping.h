#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Independent/FS/File.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct File::Mapping {

  struct View;

  typedef File::Permition Protection;

  typedef File::Size Size;
  struct Large { typedef File::Large::Size Size; };

  template <typename Size>
  Mapping(File &file, const Protection &protection, const Size &/*maxSize*/)
    : file(file) { LWF::Debug::Assert(protection & Protection::All); }

  protected: File &file;
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_H
