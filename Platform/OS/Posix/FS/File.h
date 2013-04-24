#ifndef CSHIFT_PLATFORM_OS_FS_FILE_H
#define CSHIFT_PLATFORM_OS_FS_FILE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/FS/Path.h"
#include "Platform/OS/Independent/FS/File.h"
#include "Platform/OS/API/File.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct File : protected Platform::OS::Independent::FS::File,
              protected Platform::OS::API::File {

  private: struct OS {struct Independent {
    typedef Platform::OS::Independent::FS::File Base;
  };};
  typedef Platform::OS::API::File Base; public:

  typedef OS::Independent::Base::Whence Whence;
  typedef OS::Independent::Base::Access Access;
  typedef OS::Independent::Base::Exclusive Exclusive;
  typedef OS::Independent::Base::Permition Permition;

  struct Mapping;

  File(const Path &path, const Access &access, const Exclusive &exclusive,
       const Permition::Mode &mode)
    : File::OS::Independent::Base(access, exclusive, mode),
      File::Base(path, Base::Open(
           // Acess
           (access.canReadWrite() ? Base::Open::ReadWrite :
            access.readOnly    () ? Base::Open::ReadOnly  :
            access.writeOnly   () ? Base::Open::WriteOnly : 0) |
           // Exclusive
           (exclusive.create() ? Base::Open::Create + Base::Open::Exclusive :
            exclusive.open()   ? Base::Open::Exclusive :
                                 Base::Open::Create)),
           ((mode.user << 6) | (mode.group << 3)  | (mode.other << 0))) {}

  template <typename Size>
  Void truncate(const Size &size) { Base::truncate(size); }

  template <typename Offset>
  Offset seek(const Offset &offset, const File::Whence::Seek &whence) {
    return Base::seek(offset,
                      whence == whence.Begin ? Base::Seek::Set :
                      whence == whence.End   ? Base::Seek::End   :
                                               Base::Seek::Current);
  }
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_H
