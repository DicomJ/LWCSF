#ifndef CSHIFT_PLATFORM_OS_API_FILE_MAPPING_VIEW_H
#define CSHIFT_PLATFORM_OS_API_FILE_MAPPING_VIEW_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include"Platform/OS/API/File/Mapping.h"
#include"Platform/OS/API/System/Info.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct File::Mapping::View {

  struct Access : LWF::Flags {
    enum {
      None    = 0,
      Copy    = FILE_MAP_COPY,
      Write   = FILE_MAP_WRITE,
      Read    = FILE_MAP_READ,
      All     = FILE_MAP_ALL_ACCESS,
      Execute = FILE_MAP_EXECUTE
    };
    Access(LWF::Flags::Type access) : LWF::Flags(access) {}
  };
  View(File::Mapping &mapping, const Access &access,
       LWF::Large::UInt offset, UInt size){
    static UInt pageSize = System::Info::instance().pageSize();
    UInt inPageOffset = offset.low() % pageSize;
    size += inPageOffset;
    (Result)((this->address = (Byte *)MapViewOfFile(mapping,
            access, offset.high(), offset.low() - inPageOffset, size)) != NULL);
    this->inPageAddress = this->address + inPageOffset;
  }
  ~View() { UnmapViewOfFile(address); }

  operator Bool () const  { return this->address != NULL; }
  operator Void *() const { return inPageAddress; }

  private: Byte *address;
  private: Void *inPageAddress;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_FILE_MAPPING_VIEW_H
