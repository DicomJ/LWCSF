#ifndef CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H
#define CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/File/Mapping.h"
#include "Platform/OS/Independent/FS/File/Mapping/View.h"
#include "Platform/OS/API/File/Map.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct File::Mapping::View : OS::Independent::Base::Mapping::View,
                             protected File::Base::Map {

  typedef OS::Independent::Base::Mapping::View::Protection Protection;

  template <typename Offset>
  View(File::Mapping &mapping, const Offset &offset, UInt size, Bool shared,
       const Protection &protection)
    : File::OS::Independent::Base::Mapping::View(mapping, offset, size, shared, protection),
      Base::Map((File &)mapping.file, offset, size,
                // Protection
                ((protection.canRead   () ? File::Base::Map::Protection::Read    : 0) |
                 (protection.canWrite  () ? File::Base::Map::Protection::Write   : 0) |
                 (protection.canExecute() ? File::Base::Map::Protection::Execute : 0)),
                // Flags
                (shared ? File::Base::Map::Type::Shared :
                          File::Base::Map::Type::Private)) {}
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H
