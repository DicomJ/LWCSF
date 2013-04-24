#ifndef CSHIFT_LWF_STD_DEALLOCATOR_H
#define CSHIFT_LWF_STD_DEALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Custom/Deallocator.h"


namespace CShift {
namespace LWF {

namespace Std {

struct Deallocator {
  Void deallocate(Void *ptr) const { ::operator delete (ptr); }
};


}}} // namespace CShift::LWF::Std

#endif // CSHIFT_LWF_STD_DEALLOCATOR_H
