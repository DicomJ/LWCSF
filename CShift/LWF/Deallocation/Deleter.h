#ifndef CSHIFT_LWF_DEALLOCATION_DELETER_H
#define CSHIFT_LWF_DEALLOCATION_DELETER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Deallocation {

template <typename Deallocator_>
struct Deleter : Deallocator_ {
  Deleter(const Deallocator_ &deallocator) : Deallocator_(deallocator) {}
  Void Delete(Void *ptr) { Deallocator_::deallocate(ptr); }
};

}}} // namespace CShift::LWF::Deallocation

#endif // CSHIFT_LWF_DEALLOCATION_DELETER_H
