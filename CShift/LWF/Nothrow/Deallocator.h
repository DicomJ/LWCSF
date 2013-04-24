#ifndef CSHIFT_LWF_NOTHROW_DEALLOCATOR_H
#define CSHIFT_LWF_NOTHROW_DEALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Nothrow.h"


namespace CShift {
namespace LWF {

struct Nothrow::Deallocator {
  Void deallocate(Void *ptr) const { ::operator delete (ptr, std::nothrow); }
};

}} // namespace CShift::LWF

inline CShift::LWF::Void
operator delete (CShift::LWF::Void *ptr,
                 const CShift::LWF::Nothrow &) throw() {
  return CShift::LWF::Nothrow::Deallocator().deallocate(ptr);
}

#endif // CSHIFT_LWF_NOTHROW_DEALLOCATOR_H
