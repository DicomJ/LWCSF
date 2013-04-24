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
      File::Base(path,
           // Acess
           (access.canReadWrite() ? Base::Access::All :
            access.readOnly    () ? Base::Access::Read + Base::Access::Execute :
            access.writeOnly   () ? Base::Access::Write : Base::Access::None),
           // Share
           Base::Share::Delete | (access.canWrite() ? Base::Share::None :
                                                      Base::Share::Read),
           // Exclusive create or open
           (exclusive.create() ? Base::Create::New :
            exclusive.open()   ? Base::Create::OpenExisting :
                                 Base::Create::OpenAlways),
            Base::Attribute::Normal) {}

  template <typename Size>
  Void truncate(const Size &size) {
    Size current = Base::setPointer(Size(0), Base::MoveMethod::Current);
    Base::setPointer(size, Base::MoveMethod::Begin); Base::setEnd();
    Base::setPointer(current, Base::MoveMethod::Begin);
  }


  File::Offset seek(const File::Offset &offset,
                    const File::Whence::Seek &whence) {
    return seek_(offset, whence);
  }

  File::Large::Offset seek(const File::Large::Offset &offset,
                           const File::Whence::Seek &whence) {
    return seek_(offset, whence);
  }

  private: template <typename Offset>
  Offset seek_(const Offset &offset, const File::Whence::Seek &whence) {
    return Offset(Base::setPointer(typename File::Match::Size<Offset>::Type(offset),
                    whence == whence.Begin ? Base::MoveMethod::Begin :
                    whence == whence.End   ? Base::MoveMethod::End   :
                                             Base::MoveMethod::Current));
  }
};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_FILE_H
