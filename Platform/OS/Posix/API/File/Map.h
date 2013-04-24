#ifndef CSHIFT_PLATFORM_OS_API_FILE_MAP_H
#define CSHIFT_PLATFORM_OS_API_FILE_MAP_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/File.h"
#include "LWF/Large/Integer.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Bits.h"

#include <sys/mman.h>

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct File::Map {

  struct Protection : LWF::Flags {
    enum {
      None    = PROT_NONE,
      Read    = PROT_READ,
      Write   = PROT_WRITE,
      Execute = PROT_EXEC
    };
    Protection(LWF::Flags::Type protection) : LWF::Flags(protection) {}
  };

  struct Type : LWF::Flags {
    enum {
      Shared  = MAP_SHARED,
      Private = MAP_PRIVATE
    };
    Type(LWF::Flags::Type type) : LWF::Flags(type) {}
  };

  typedef LWF::Flags Flags;


  Map(File &file, UInt offset, UInt size,
       const Protection &protection, const Flags &flags, Void *address = NULL) {

    static const UInt pageSize = sysconf(_SC_PAGE_SIZE);
    UInt inPageOffset = offset % pageSize;
    UInt pageOffset = offset - inPageOffset;
    this->size = size + inPageOffset;
    (this->address = (Byte *)
        mmap(
          address, this->size,
          protection, flags,
          file, pageOffset)), Result::asBool(*this);
    this->inPageAddress = this->address + inPageOffset;
  }

  Map(File &file, const LWF::Large::UInt &offset, UInt size,
      const Protection &protection, const Flags &flags, Void *address = NULL) {
    #if PLATFORM_COMPILER_64BITS_INTEGER
      static const UInt64 pageSize = sysconf(_SC_PAGE_SIZE);
      UInt inPageOffset = UInt64(offset) % pageSize;
      UInt pageOffset = UInt64(offset) - inPageOffset;
      this->size = size + inPageOffset;
      (this->address = (Byte *)
          mmap64(
            address, this->size,
            protection, flags,
            file, pageOffset)), Result::asBool(*this);
      this->inPageAddress = this->address + inPageOffset;

    #else // !PLATFORM_COMPILER_64BITS_INTEGER
      #if 0 // TODO; look for mmap2
        UInt inPageOffset = LWF::Bits32(offset)[LWF::Bits32::Low<12>()];
        UInt pageOffset = offset >> UInt(12);
        this->size = size + inPageOffset;
        (this->address = (Byte *)
            mmap2(
              address, this->size,
              protection, flags,
              file, pageOffset)), Result::asBool(*this);
        this->inPageAddress = this->address + inPageOffset;
      #else
        static const UInt pageSize = sysconf(_SC_PAGE_SIZE);
        UInt inPageOffset = offset % pageSize;
        UInt pageOffset = offset - LWF::Large::UInt(inPageOffset);
        this->size = size + inPageOffset;
        (this->address = (Byte *)
            mmap(
              address, this->size,
              protection, flags,
              file, pageOffset)), Result::asBool(*this);
        this->inPageAddress = this->address + inPageOffset;
      #endif
    #endif // !PLATFORM_COMPILER_64BITS_INTEGER
  }

  ~Map() { munmap(address, size); }

  operator Bool () const  { return this->address != MAP_FAILED; }
  operator Void *() const { return inPageAddress; }

  private: Byte *address;
  private: UInt size;
  private: Void *inPageAddress;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_FILE_MAP_H
