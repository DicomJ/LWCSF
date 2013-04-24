#ifndef CSHIFT_LWF_WEAK_BUFFER_H
#define CSHIFT_LWF_WEAK_BUFFER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Array.h"


namespace CShift {
namespace LWF {
namespace Weak {

typedef LWF::Weak::Array<Byte> Buffer;

namespace Const {
  typedef LWF::Weak::Array<const Byte> Buffer;
}

}}} // namespace CShift::LWF::Weak

#endif // CSHIFT_LWF_WEAK_BUFFER_H
