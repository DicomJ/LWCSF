#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_VIEW_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_VIEW_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/Independent/FS/File/Mapping.h"
#include "LWF/Debug/Assert.h"
#include "LWF/Traits/Prediction.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct File::Mapping::View {

  typedef File::Mapping::Protection Protection;
  typedef File::Mapping::Size Offset;
  struct Large { typedef File::Mapping::Large::Size Offset; };

  template <typename Offset>
  View(File::Mapping &mapping, const Offset &/*offset*/, UInt size,
       Bool/* shared*/, const Protection &/*protection*/,
       const typename LWF::Traits::Prediction<
          LWF::Type<Offset>::Is::Castable::template To<
            typename File::Mapping::View::Offset>::type ||
          LWF::Type<Offset>::Is::Castable::template To<
            typename File::Mapping::View::Large::Offset>::type>::Type & = null)
    : mapping(mapping) {
    LWF::Debug::Assert(size != 0);
  }

  protected: File::Mapping &mapping;
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_MAPPING_VIEW_H
