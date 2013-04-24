#ifndef CSHIFT_PLATFORM_OS_FS_PATH_H
#define CSHIFT_PLATFORM_OS_FS_PATH_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/String.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace FS {

struct Path : Platform::OS::API::String {

  private: typedef Platform::OS::API::String Base; public:

  Path(const Platform::OS::API::String &path) : Base(path) {}

};

}}}} // namespace CShift::Platform::OS::FS

#endif // CSHIFT_PLATFORM_OS_FS_PATH_H
