#ifndef CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H
#define CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/File.h"
#include "Platform/OS/Independent/FS/File/Mapping.h"
#include "Platform/OS/API/File/Mapping.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct File::Mapping : File::OS::Independent::Base::Mapping,
                       protected File::Base::Mapping {
  struct View;

  typedef File::OS::Independent::Base::Mapping::Protection Protection;

  template <typename Size>
  Mapping(File &file, const Protection &protection, const Size &maxSize)
    : File::OS::Independent::Base::Mapping(file, protection, maxSize),
      File::Base::Mapping(file,
        protection.canExecute() ?
          (protection.canReadWrite() ?
             File::Base::Mapping::Protection::ExecuteReadWrite :
           protection.canRead() ?
             File::Base::Mapping::Protection::ExecuteRead :
           protection.canWrite() ?
             File::Base::Mapping::Protection::ExecuteWriteCopy :
             File::Base::Mapping::Protection::Execute)
        : (protection.canReadWrite() ?
             File::Base::Mapping::Protection::ReadWrite :
           protection.canRead() ?
             File::Base::Mapping::Protection::ReadOnly :
           protection.canWrite() ?
             File::Base::Mapping::Protection::WriteCopy :
             File::Base::Mapping::Protection::NoAccess),
           maxSize) {}
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_H
