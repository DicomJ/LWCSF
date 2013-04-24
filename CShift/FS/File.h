#ifndef CSHIFT_FS_FILE_H
#define CSHIFT_FS_FILE_H

#include "FS/License"
#include "Author/Andriy.Bulka"

#include "FS/Path.h"
#include "Platform/OS/FS/File.h"

namespace CShift {
namespace FS {

struct File : protected Platform::OS::FS::File {
  private: typedef Platform::OS::FS::File Base; public:

  struct Mapping;

  typedef Base::Access Access;
  typedef Base::Exclusive Exclusive;
  typedef Base::Permition Permition;
  typedef Base::Whence Whence;

  typedef Base::Size Size;
  typedef Base::Offset Offset;
  struct Large { typedef Base::Large::Size Size;
                 typedef Base::Large::Offset Offset; };

  typedef FS::Path Path;

  File(const Path &path,
       const Access &access = Access::ReadWrite,
       const Exclusive &exclusive = Exclusive::None,
       const Permition::Mode &mode = Permition::Mode(Permition::ReadWrite,
                                                     Permition::ReadWrite,
                                                     Permition::ReadWrite))
    : Base(path, access, exclusive, mode) {}

  template <typename Size>
  File &truncate(const Size &size) { Base::truncate(size); return *this; }

  template <typename Size>
  Size seek(const Size &size,
            const File::Whence::Seek &whence = File::Whence::Seek::Begin) {
    return Base::seek(size, whence);
  }

  template <UInt whence, typename Offset>
  Offset seek(const Offset &offset) { return seek(offset, File::Whence::Seek(whence)); }

  template <typename Size>
  Size tell() { return seek<File::Whence::Seek::Begin>(Size(0)); }
};

}} // namespace CShift::FS

#endif // CSHIFT_FS_FILE_H
