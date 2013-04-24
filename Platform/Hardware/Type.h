#ifndef PLATFORM_HARDWARE_TYPE_H
#define PLATFORM_HARDWARE_TYPE_H

#include "Platform/License"
#include "Author/Andriy.Bulka"

#include "Platform/Hardware/Type/Traits/Boolean.h"
#include "Platform/Hardware/Type/Traits/Integer.h"
#include "Platform/Hardware/Type/Traits/Character.h"
#include "Platform/Hardware/Type/Traits/Real.h"
#include "Platform/Hardware/Type/Traits/Pointer.h"
#include "Platform/Hardware/Type/Traits/Nonfundamental.h"


namespace Platform {
namespace Hardware {
namespace Type {

namespace Declaration {
  using namespace Type::Boolean;
  using namespace Type::Integer;
  using namespace Type::Character;
  using namespace Type::Real;
  using namespace Type::Pointer;
  using namespace Type::Nonfundamental;
}

}}} // namespace Platform::Hardware::Type

#endif // PLATFORM_HARDWARE_TYPE_H
