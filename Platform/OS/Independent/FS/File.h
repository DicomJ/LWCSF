#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "LWF/Enum.h"
#include "LWF/Debug/Assert.h"
#include "Platform/OS/Independent/FS/Object/Permition/Mode.h"
#include "LWF/Large/Integer.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace FS {

struct File : Platform::OS::Independent::FS::Object {

  struct Mapping;  

  typedef Int   Offset;
  typedef UInt  Size;

  struct Large {
    typedef LWF::Large::Int   Offset;
    typedef LWF::Large::UInt  Size;
  };

//  typedef Object::Access Access;
//  typedef Object::Permition Permition;

  struct Exclusive : LWF::Enum {
    enum { // Can be one of the following:
      None    = 0,  // Creates a non-existing or opens an existing file
      Open    = 1,  // Fails if a file doesn't exist
      Create  = 2   // Fails if a file exists
    };

    Bool open  () const { return *this & Open; }
    Bool create() const { return *this & Create; }

    operator Bool() const { return *this != None; }

    Exclusive(LWF::Enum::Type exclusive = None) : LWF::Enum(exclusive) {
      LWF::Debug::Assert(Create >= *this);
      LWF::Debug::Assert((Open + Create) != *this);
    }
  };

  struct Whence {
    struct Seek : LWF::Enum {
      enum { Begin, Current, End };

      Seek(LWF::Enum::Type whence) : LWF::Enum(whence) {
        LWF::Debug::Assert(Begin == whence || Current == whence || End == whence);
      }
    }; private: Whence();
  };

  File(const Access &access, const Exclusive &/*exclusive*/,
       const Permition::Mode &/*mode*/) {
    LWF::Debug::Assert(access != access.None);
  }

  protected: struct Match {
    template <typename Offset, typename U = Void>
    struct Size;
    template <typename U>
    struct Size<File::Offset, U> { typedef File::Size Type; };
    template <typename U>
    struct Size<File::Large::Offset, U> { typedef File::Large::Size Type; };

    template <typename Size, typename U = Void>
    struct Offset;
    template <typename U>
    struct Offset<File::Size, U> { typedef File::Offset Type; };
    template <typename U>
    struct Offset<File::Large::Size, U> { typedef File::Large::Offset Type; };
  };
};

}}}}} // namespace CShift::Platform::OS::Independent::FS

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_FS_FILE_H
