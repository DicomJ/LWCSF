#ifndef CSHIFT_LWF_TYPE_DECLARATION_H
#define CSHIFT_LWF_TYPE_DECLARATION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "CShift/Platform/Hardware/Type.h"


namespace CShift {
namespace LWF {

namespace Types {
using namespace Platform::Hardware::Type::Declaration;
} // Types

using namespace LWF::Types;
namespace Kind { using namespace Platform::Hardware::Type::Kind; }
}} // namespace CShift::LWF

namespace CShift {
using namespace LWF::Types;
} // namespace CShift

#endif // CSHIFT_LWF_TYPE_DECLARATION_H
