#ifndef CSHIFT_FS_FILE_MAPPING_VIEW_H
#define CSHIFT_FS_FILE_MAPPING_VIEW_H

#include "FS/License"
#include "Author/Andriy.Bulka"

#include "FS/File/Mapping.h"
#include "Platform/OS/FS/File/Mapping/View.h"

namespace CShift {
namespace FS {

struct File::Mapping::View : protected Platform::OS::FS::File::Mapping::View {

  private: typedef Platform::OS::FS::File::Mapping::View Base; public:

  typedef Base Offset;
  struct Large { typedef Base::Large::Offset Offset; };
  typedef Base::Protection Protection;

  template <typename Offset>
  View(File::Mapping &mapping, const Offset &offset, UInt size, Bool shared = True,
       const Protection &protection = Protection::ReadWrite)
    : Base(mapping, offset, size, shared, protection) {}

  operator Void *() const { return Base::operator Void * (); }
};

}} // namespace CShift::FS

#endif // CSHIFT_FS_FILE_MAPPING_VIEW_H
