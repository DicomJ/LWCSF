#ifndef CSHIFT_LWF_CUSTOM_ARRAY_ALLOCATOR_H
#define CSHIFT_LWF_CUSTOM_ARRAY_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Custom/Allocator/Cast.h"
#include "LWF/Custom/Array/Deallocator.h"

template <typename Allocator>
inline CShift::LWF::Void *
operator new[] (CShift::LWF::UInt32 size, Allocator &allocator) {
  return CShift::LWF::Custom::Allocator::Cast<Allocator>::allocator(allocator).allocate(size);
}
template <typename Allocator>
inline CShift::LWF::Void *
operator new[] (CShift::LWF::UInt32 size, const Allocator &allocator) {
  return CShift::LWF::Custom::Allocator::Cast<Allocator>::allocator(allocator).allocate(size);
}

#endif // CSHIFT_LWF_CUSTOM_ARRAY_ALLOCATOR_H
