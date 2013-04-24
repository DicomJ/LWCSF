#ifndef PLATFORM_HARDWARE_TYPE_KIND_DEF_H
#define PLATFORM_HARDWARE_TYPE_KIND_DEF_H

#include "Platform/License"
#include "Author/Andriy.Bulka"


namespace Platform {
namespace Hardware {
namespace Type {
namespace Kind {
  
template <typename K> struct Def { typedef K Kind; };

}}}} // namespace Platform::Hardware::Type::Kind

#endif // PLATFORM_HARDWARE_TYPE_KIND_DEF_H
