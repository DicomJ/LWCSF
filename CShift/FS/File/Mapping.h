#ifndef CSHIFT_FS_FILE_MAPPING_H
#define CSHIFT_FS_FILE_MAPPING_H

#include "FS/License"
#include "Author/Andriy.Bulka"

#include "FS/File.h"
#include "Platform/OS/FS/File/Mapping.h"

namespace CShift {
namespace FS {

struct File::Mapping : protected Platform::OS::FS::File::Mapping {

  private: typedef Platform::OS::FS::File::Mapping Base; public:

  struct View;

  typedef Base::Protection Protection;
  typedef Base::Size Size;
  struct Large { typedef Base::Large::Size Size; };

  Mapping(File &file, const Protection &protection = Protection::ReadWrite, const Size &maxSize = 0)
    : Base(file, protection, maxSize) {}

  Mapping(File &file, const Protection &protection, const Large::Size &maxSize)
    : Base(file, protection, maxSize) {}
};

}} // namespace CShift::FS

#endif // CSHIFT_FS_FILE_MAPPING_H
