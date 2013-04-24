#ifndef PLATFORM_HARDWARE_TYPE_KIND_INTEGER_H
#define PLATFORM_HARDWARE_TYPE_KIND_INTEGER_H

#include "Platform/License"
#include "Author/Andriy.Bulka"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {

struct Integer { template<typename T, bool isSigned = (T(-1) < 0)> struct Traits;
  struct Signed { template<typename T> struct Traits; };
  struct Unsigned { template<typename T> struct Traits; };
};

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_INTEGER_H
