#ifndef CSHIFT_PLATFORM_OS_API_FILE_MAPPING_H
#define CSHIFT_PLATFORM_OS_API_FILE_MAPPING_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include"Platform/OS/API/File.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct File::Mapping : Handle<UInt(NULL)> {

  private: typedef Handle<UInt(NULL)> Base; public:

  struct View;

  struct Protection : LWF::Flags {
    enum {
      NoAccess          = PAGE_NOACCESS,
      ReadOnly          = PAGE_READONLY,
      ReadWrite         = PAGE_READWRITE,
      WriteCopy         = PAGE_WRITECOPY,
      Execute           = PAGE_EXECUTE,
      ExecuteRead       = PAGE_EXECUTE_READ,
      ExecuteReadWrite  = PAGE_EXECUTE_READWRITE,
      ExecuteWriteCopy  = PAGE_EXECUTE_WRITECOPY
    };
    Protection(LWF::Flags::Type protection) : LWF::Flags(protection) {}
  };

  struct Attribute : LWF::Flags {
    enum {
      Image           = SEC_IMAGE,
      ProtectedImage  = SEC_PROTECTED_IMAGE,
      Reserve         = SEC_RESERVE,
      Commit          = SEC_COMMIT,
      NoCache         = SEC_NOCACHE,
      WriteCombine    = SEC_WRITECOMBINE,
      LargePages      = SEC_LARGE_PAGES
    };
    Attribute(LWF::Flags::Type attribute) : LWF::Flags(attribute) {}
  };

  Mapping(File &file, const Protection &protection,
          LWF::Large::UInt maxSize, // TODO
          const Security::Attributes::Optional::Ptr securityAttributes = null,
          const String &name = String())
    : Base(CreateFileMapping(file,
                             Security::Attributes::Optional::ptr(securityAttributes),
                             protection, maxSize.high(), maxSize.low(),
                             Platform::OS::API::Optional::lpctstr(name))) {}
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_FILE_MAPPING_H
