#ifndef CSHIFT_LWF_VALUE_SWAP_H
#define CSHIFT_LWF_VALUE_SWAP_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value.h"
#include "LWF/Boolean/Constant.h"


namespace CShift {
namespace LWF {

namespace {
template <typename Type, Bool = LWF::Type<Type>::Is::swapable>
struct Swap {
  Swap(Type &This, Type &value) {
    This.swap(value);
  }
};

template <typename Type>
struct Swap<Type, False> {
  Swap(Type &This, Type &value) {
    if (&This != &value) {
      Type tmp = This; This = value; value = tmp;
    }
  }
};
}

template <typename Type>
Void Value<Type>::swap(const Value &value) const {
  swap(static_cast<Type &>(value));
}

template <typename Type>
Void Value<Type>::swap(Type &value) const {
  Swap<Type>(*this, value);
}

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VALUE_SWAP_H
