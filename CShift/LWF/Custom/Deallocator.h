#ifndef CSHIFT_LWF_CUSTOM_DEALLOCATOR_H
#define CSHIFT_LWF_CUSTOM_DEALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Custom/Allocator/Cast.h"

template <typename Deallocator>
inline CShift::LWF::Void
operator delete (CShift::LWF::Void *ptr, Deallocator &deallocator) {
  CShift::LWF::Custom::Allocator::Cast<Deallocator>
      ::deallocator(deallocator).deallocate(ptr);
}
template <typename Deallocator>
inline CShift::LWF::Void
operator delete (CShift::LWF::Void *ptr, const Deallocator &deallocator) {
  CShift::LWF::Custom::Allocator::Cast<Deallocator>
      ::deallocator(deallocator).deallocate(ptr);
}

#endif // CSHIFT_LWF_CUSTOM_DEALLOCATOR_H
