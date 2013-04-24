#ifndef CSHIFT_LWF_DESTROYING_DELETER_H
#define CSHIFT_LWF_DESTROYING_DELETER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Destroying {

template <typename T, typename Deallocator_>
struct Deleter : Deallocator_ {
  Deleter(const Deallocator_ &deallocator) : Deallocator_(deallocator) {}
  Void Delete(T *ptr) const { ptr->~T(); Deallocator_::deallocate(ptr); }
};

template <typename T, typename Deallocator_>
struct Deleter <T[], Deallocator_> : Deallocator_ {
  Deleter(const Deallocator_ &deallocator) : Deallocator_(deallocator) {}
  Void Delete(T *ptr, UInt count) const {
    while(count != 0) { ptr[--count].~T(); }
    Deallocator_::deallocate(ptr);
  }
};

}}} // namespace CShift::LWF::Destroying

#endif // CSHIFT_LWF_DESTROYING_DELETER_H
