#ifndef CSHIFT_LWF_PLACEMENT_ALLOCATOR_H
#define CSHIFT_LWF_PLACEMENT_ALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Placement/Deallocator.h"


namespace CShift {
namespace LWF {
namespace Placement {

struct Allocator : LWF::Placement::Deallocator {
  Allocator(Void *ptr_) : ptr(ptr_) {}
  Void *allocate(UInt ) const { return ptr; }
  private: Void *ptr;
};

}}} // namespace CShift::LWF::Placement


#include "LWF/Custom/Allocator/Cast.h"
#include "LWF/Custom/Allocator.h"
#include "LWF/Custom/Array/Allocator.h"


namespace CShift {
namespace LWF {
namespace Custom {
namespace Allocator {

template <typename Pointer>
struct Cast<Pointer, True> {
  static LWF::Placement::Allocator
  allocator(Pointer ptr) { return LWF::Placement::Allocator(ptr); }
  static LWF::Placement::Deallocator
  deallocator(Pointer) { return LWF::Placement::Deallocator(); }
};

}}}} // namespace CShift::LWF::Custom::Allocator

#endif // CSHIFT_LWF_PLACEMENT_ALLOCATOR_H
