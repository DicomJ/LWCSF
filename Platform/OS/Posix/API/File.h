#ifndef CSHIFT_PLATFORM_OS_API_FILE_H
#define CSHIFT_PLATFORM_OS_API_FILE_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/String.h"
#include "Platform/OS/API/Result.h"
#include "Platform/OS/API/Mode.h"
#include "LWF/Flags.h"
#include "LWF/Large/Integer.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct File {

  struct Map;

  struct Open : LWF::Flags {
    enum {
      ReadOnly  = O_RDONLY,
      WriteOnly = O_WRONLY,
      ReadWrite = O_RDWR,

      Create    = O_CREAT,
      Exclusive = O_EXCL
    };

    Open(LWF::Flags::Type open) : LWF::Flags(open) {}
  };

  struct Seek: LWF::Enum {
    enum {
      Set = SEEK_SET,
      Current = SEEK_CUR,
      End = SEEK_END
    };
    Seek(LWF::Enum::Type seek) : LWF::Enum(seek) {}
  };

  File(const String &path, const Open &flags, const Mode &mode) {
    (fd = open(&*path.cstring(), flags, mode)), Result::asBool(*this);
  }
  ~File() { if (*this) { close(*this); } }

  Void truncate(UInt size) { ftruncate(*this, size); }
  Void truncate(const LWF::Large::UInt &size) { ftruncate64(*this, size); }

  Int seek(Int offset, const Seek &whence) {
    return lseek(*this, offset, whence);
  }
  #if PLATFORM_COMPILER_64BITS_INTEGER
  LWF::Large::Int seek(const LWF::Large::Int &offset, const Seek &whence) {
    return Int64(lseek64(*this, Int64(offset), whence));
  }
  #else
  LWF::Large::Int seek(const LWF::Large::Int &offset, const Seek &whence) {
    #if 0 // TODO: lookup for llseek
      return _llseek(*this, offset.high(), offset.low(), whence);
    #else
      return Int32(lseek(*this, Int32(offset.low()), whence));
    #endif
  }
  #endif


  operator Bool () const { return fd != -1; }
  private: operator Int () const { return fd; }
  private: Int fd;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_FILE_H
