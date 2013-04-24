#ifndef CSHIFT_LWF_FORWARD_REFERENCE_H
#define CSHIFT_LWF_FORWARD_REFERENCE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/No/Reference.h"


namespace CShift {
namespace LWF {
namespace Forward {

#if PLATFORM_COMPILER_RVALUE_REFERENCE

template <typename Type>
Type &&reference(typename LWF::Traits::No::Reference<Type>::Type  &value) {
  return static_cast<Type &&>(value);
}
template <typename Type>
Type &&reference(typename LWF::Traits::No::Reference<Type>::Type &&value) {
  return static_cast<Type &&>(value);
}

#else  // !C++11

template <typename Type>
Type &reference(typename LWF::Traits::No::Reference<Type>::Type  &value) {
  return static_cast<Type &>(value);
}

#endif // !C++11

}}} // namespace CShift::LWF::Forward

#endif // CSHIFT_LWF_FORWARD_REFERENCE_H
