#ifndef CSHIFT_LWF_STD_ARRAY_ALLOCATOR_H
#define CSHIFT_LWF_STD_ARRAY_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Std/Array/Deallocator.h"
#include "LWF/Custom/Array/Allocator.h"


namespace CShift {
namespace LWF {
namespace Std {
namespace Array {

struct Allocator : LWF::Std::Array::Deallocator {
  Void *allocate(UInt size) const { return ::operator new [] (size); }
};

}}}} // namespace CShift::LWF::Std::Array

#endif // CSHIFT_LWF_STD_ARRAY_ALLOCATOR_H
