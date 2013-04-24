#ifndef CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H
#define CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/File/Mapping.h"
#include "Platform/OS/Independent/FS/File/Mapping/View.h"
#include "Platform/OS/API/File/Mapping/View.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct File::Mapping::View : File::OS::Independent::Base::Mapping::View,
                             protected File::Base::Mapping::View {

  typedef File::OS::Independent::Base::Mapping::View::Protection Protection;

  template <typename Offset>
  View(File::Mapping &mapping, const Offset &offset, UInt size, Bool shared,
       const Protection &protection)
    : File::OS::Independent::Base::Mapping::View(mapping, offset, size, shared, protection),
      File::Base::Mapping::View(mapping,
        // Protection
        (protection.canWrite  () ? (shared ? File::Base::Mapping::View::Access::Write :
                                             File::Base::Mapping::View::Access::Copy):
         protection.canRead   () ? File::Base::Mapping::View::Access::Read :
                                   File::Base::Mapping::View::Access::None) |
         (protection.canExecute() ? File::Base::Mapping::View::Access::Execute :
                                    File::Base::Mapping::View::Access::None),
         offset, size) {}
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_MAPPING_VIEW_H
