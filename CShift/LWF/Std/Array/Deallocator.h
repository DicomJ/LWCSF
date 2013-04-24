#ifndef CSHIFT_LWF_STD_ARRAY_DEALLOCATOR_H
#define CSHIFT_LWF_STD_ARRAY_DEALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Custom/Array/Deallocator.h"


namespace CShift {
namespace LWF {
namespace Std {
namespace Array {

struct Deallocator {
  Void deallocate(Void *ptr) const { ::operator delete [] (ptr); }
};

}}}} // namespace CShift::LWF::Std::Array

#endif // CSHIFT_LWF_STD_ARRAY_DEALLOCATOR_H
