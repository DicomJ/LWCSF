#ifndef CSHIFT_PLATFORM_OS_API_FILE_H
#define CSHIFT_PLATFORM_OS_API_FILE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Handle.h"
#include "Platform/OS/API/String.h"
#include "Platform/OS/API/Security/Attributes.h"
#include "Platform/OS/API/Result.h"
#include "LWF/Flags.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Large/Integer.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

class File : Handle<UInt(-1/*INVALID_HANDLE_VALUE*/)> {

  typedef Handle<UInt(-1/*INVALID_HANDLE_VALUE*/)> Base; public:

  struct Optional {
    typedef LWF::Weak::Ptr<File> Ptr;
    static Base::Type ptr(const Ptr &ptr) {
      return ptr != null ? *ptr: Base::Type(NULL);
    }
  };

  struct Access : LWF::Flags {
    enum {
      None    = 0,
      Read    = GENERIC_READ,
      Write   = GENERIC_WRITE,
      Execute = GENERIC_EXECUTE,
      All     = GENERIC_ALL
    };
    Access(LWF::Flags::Type open) : LWF::Flags(open) {}
  };

  struct Share : LWF::Flags {
    enum {
      None    = 0,
      Read    = FILE_SHARE_READ,
      Write   = FILE_SHARE_WRITE,
      Delete  = FILE_SHARE_DELETE
    };
    Share(LWF::Flags::Type shared) : LWF::Flags(shared) {}
  };

  struct Create : LWF::Flags {
    enum {
      New               = CREATE_NEW,
      Always            = CREATE_ALWAYS,
      OpenExisting      = OPEN_EXISTING,
      OpenAlways        = OPEN_ALWAYS,
      TruncateExisting  = TRUNCATE_EXISTING
    };
    Create(LWF::Flags::Type create) : LWF::Flags(create) {}
  };

  struct Attribute : LWF::Flags {
    enum {
      ReadOnly          = FILE_ATTRIBUTE_READONLY,
      Hidden            = FILE_ATTRIBUTE_HIDDEN,
      System            = FILE_ATTRIBUTE_SYSTEM,
      Directory         = FILE_ATTRIBUTE_DIRECTORY,
      Archive           = FILE_ATTRIBUTE_ARCHIVE,
      Device            = FILE_ATTRIBUTE_DEVICE,
      Normal            = FILE_ATTRIBUTE_NORMAL,
      Temporary         = FILE_ATTRIBUTE_TEMPORARY,
      Compressed        = FILE_ATTRIBUTE_COMPRESSED,
      Offline           = FILE_ATTRIBUTE_OFFLINE,
      NotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
      Encrypted         = FILE_ATTRIBUTE_ENCRYPTED,
      Virtual           = FILE_ATTRIBUTE_VIRTUAL
    };
    Attribute(LWF::Flags::Type attribute) : LWF::Flags(attribute) {}
  };

  struct Flag : LWF::Flags {
    enum {
      WriteThrough      = FILE_FLAG_WRITE_THROUGH,
      Overlapped        = FILE_FLAG_OVERLAPPED,
      NoBuffering       = FILE_FLAG_NO_BUFFERING,
      RandomAccess      = FILE_FLAG_RANDOM_ACCESS,
      SequentialScan    = FILE_FLAG_SEQUENTIAL_SCAN,
      DeleteOnClose     = FILE_FLAG_DELETE_ON_CLOSE,
      BackupSemantics   = FILE_FLAG_BACKUP_SEMANTICS,
      PosixSemantics    = FILE_FLAG_POSIX_SEMANTICS,
      OpenReparsePoint  = FILE_FLAG_OPEN_REPARSE_POINT,
      OpenNoRecall      = FILE_FLAG_OPEN_NO_RECALL,
      FirstPipeInstance = FILE_FLAG_FIRST_PIPE_INSTANCE
    };
    Flag(LWF::Flags::Type flag) : LWF::Flags(flag) {}
  };

  struct MoveMethod : LWF::Enum {
    enum {
      Begin   = FILE_BEGIN,
      Current = FILE_CURRENT,
      End     = FILE_END
    };
    MoveMethod(LWF::Enum::Type moveMethod) : LWF::Enum(moveMethod) {}
  };

  struct Mapping;

  File(const String &path, const Access &access, const Share &share,
       const LWF::Flags &createOrOpen, LWF::Flags flagsAndAttributes,
       const File::Optional::Ptr templateFile = null,
       const Security::Attributes::Optional::Ptr securityAttributes = null)
    : Base(CreateFile(&*path.cstring(), access, share,
                      Security::Attributes::Optional::ptr(securityAttributes),
                      createOrOpen, flagsAndAttributes,
                      Optional::ptr(templateFile))) {}

//  Int setPointer(Int size, const MoveMethod &moveMethod) {
//    return Int(setPointer(Int(size), moveMethod));
//  }

  UInt setPointer(UInt size, const MoveMethod &moveMethod) {
    DWORD result = SetFilePointer(*this, size, NULL, moveMethod);
    return Result(result != INVALID_SET_FILE_POINTER), result;
  }

//  LWF::Large::Int setPointer(const LWF::Large::Int &size,
//                              const MoveMethod &moveMethod) {
//    LWF::Large::UInt offset =
//            setPointer(LWF::Large::UInt(size.low(), size.high()), moveMethod);
//    return LWF::Large::Int(offset.low(), offset.high());
//  }

  LWF::Large::UInt setPointer(const LWF::Large::UInt &size,
                              const MoveMethod &moveMethod) {
    LONG high = size.high();
    DWORD low = SetFilePointer(*this, size.low(), &high, moveMethod);
    return Result(low != INVALID_SET_FILE_POINTER), LWF::Large::UInt(low, high);
  }

  Void setEnd() { SetEndOfFile(*this); }
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_FILE_H
