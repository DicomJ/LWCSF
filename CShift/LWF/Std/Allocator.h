#ifndef CSHIFT_LWF_STD_ALLOCATOR_H
#define CSHIFT_LWF_STD_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Std/Deallocator.h"
#include "LWF/Custom/Deallocator.h"


namespace CShift {
namespace LWF {
namespace Std {

struct Allocator : LWF::Std::Deallocator {
  Void *allocate(UInt size) const { return ::operator new (size); }
};

}}} // namespace CShift::LWF::Std

#endif // CSHIFT_LWF_STD_ALLOCATOR_H
