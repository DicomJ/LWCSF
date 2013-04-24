#ifndef CSHIFT_LWF_FLAGS_H
#define CSHIFT_LWF_FLAGS_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Flags.h"

namespace CShift {
namespace LWF {

struct Flags : Traits::Flags<4> {
  Flags(Traits::Flags<4>::Type flags) : Traits::Flags<4>(flags) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_FLAGS_H
