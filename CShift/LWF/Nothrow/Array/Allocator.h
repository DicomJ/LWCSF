#ifndef CSHIFT_LWF_NOTHROW_ARRAY_ALLOCATOR_H
#define CSHIFT_LWF_NOTHROW_ARRAY_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Nothrow.h"
#include "LWF/Nothrow/Array/Deallocator.h"


namespace CShift {
namespace LWF {

struct Nothrow::Array::Allocator : Nothrow::Array::Deallocator {
  Void *allocate(UInt size) const { return ::operator new [] (size, std::nothrow); }
};

}} // namespace CShift::LWF

inline CShift::LWF::Void *
operator new[] (CShift::LWF::UInt32 size,
                const CShift::LWF::Nothrow &) throw() {
  return CShift::LWF::Nothrow::Array::Allocator().allocate(size);
}

#endif // CSHIFT_LWF_NOTHROW_ARRAY_ALLOCATOR_H
