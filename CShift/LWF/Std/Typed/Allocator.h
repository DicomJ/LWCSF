#ifndef CSHIFT_LWF_STD_TYPED_TYPED_ALLOCATOR_H
#define CSHIFT_LWF_STD_TYPED_TYPED_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Std/Allocator.h"
#include "LWF/Std/Array/Allocator.h"


namespace CShift {
namespace LWF {
namespace Std {
namespace Typed {

template <typename T>
struct Allocator : LWF::Std::Allocator {
  T * allocate () const {
    return reinterpret_cast<T *>(LWF::Std::Allocator::allocate(sizeof(T)));
  }
};

template <typename T>
struct Allocator<T[]> : LWF::Std::Array::Allocator {
  T * allocate (UInt count) const {
    return reinterpret_cast<T *>(LWF::Std::Array::Allocator::allocate(count * sizeof(T)));
  }
};

}}}} // namespace CShift::LWF::Std::Typed

#endif // CSHIFT_LWF_STD_TYPED_TYPED_ALLOCATOR_H
