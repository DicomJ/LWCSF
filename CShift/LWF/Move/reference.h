#ifndef CSHIFT_LWF_MOVE_REFERENCE_H
#define CSHIFT_LWF_MOVE_REFERENCE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/No/Reference.h"


namespace CShift {
namespace LWF {
namespace Move {

#if PLATFORM_COMPILER_RVALUE_REFERENCE

template <typename Type,
          typename Type_ = typename LWF::Traits::No::Reference<Type>::Type &&>
Type_ reference(Type &&value) { return static_cast<Type_>(value); }

#else  // !C++11

template <typename Type> typename LWF::Traits::No::Reference<Type>::Type &
reference(Type &value) {
  return static_cast<typename LWF::Traits::No::Reference<Type>::Type & >(value);
}

#endif // !C++11

}}} // namespace CShift::LWF::Move

#endif // CSHIFT_LWF_MOVE_REFERENCE_H
