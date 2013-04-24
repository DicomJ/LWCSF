#ifndef CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_ALLOCATOR_H
#define CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Std/Typed/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Vector {

template <typename Type>
struct Allocator : LWF::Std::Typed::Allocator<Type[]> {

  UInt maxSize() const {
    return (LWF::Type<UInt32>::max - LWF::Type<UInt8>::max) /
            LWF::Type<Type>::size;
  }

  UInt expanse(UInt/* capacity*/, UInt count, UInt size) const {
    return (count + size) / 2;
  }
};

}}}}} // namespace CShift::LWF::Collection::Reversible::Vector

#endif // CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_ALLOCATOR_H
