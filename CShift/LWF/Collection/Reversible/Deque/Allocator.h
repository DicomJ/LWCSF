#ifndef CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_ALLOCATOR_H
#define CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Reversible/Vector/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Deque {

template <typename Type, UInt blockSize = 128>
struct Allocator : LWF::Collection::Reversible::Vector::Allocator<Type> {
  struct Block { static const UInt size = blockSize; };
  struct Rebind {
    template <typename U>
    struct With : LWF::Collection::Reversible::Vector::Allocator<U/* == Block*/> {
      With(const Allocator &) {}
    };
  };
};

}}}}} // namespace CShift::LWF::Collection::Reversible::Deque

#endif // CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_ALLOCATOR_H
