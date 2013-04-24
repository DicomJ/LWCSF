#ifndef CSHIFT_LWF_TRAITS_LAME_H
#define CSHIFT_LWF_TRAITS_LAME_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "CShift/Platform/Hardware/Type.h"

namespace CShift {
namespace LWF {
namespace Traits {

using namespace Platform::Hardware::Type::Declaration; // for Void type

template<typename Type>
Void Lame(const Type &) { /* Laming an input parameter */ }

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_LAME_H
