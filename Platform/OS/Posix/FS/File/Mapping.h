#ifndef CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H
#define CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/File.h"
#include "Platform/OS/Independent/FS/File/Mapping.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct File::Mapping : OS::Independent::Base::Mapping {

  struct View;

  typedef File::OS::Independent::Base::Mapping::Protection Protection;

  template <typename Size>
  Mapping(File &file, const Protection &protection, const Size &maxSize)
    : File::OS::Independent::Base::Mapping(file, protection, maxSize){}
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H
