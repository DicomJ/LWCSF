#ifndef CSHIFT_LWF_PLACEMENT_DEALLOCATOR_H
#define CSHIFT_LWF_PLACEMENT_DEALLOCATOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {

namespace Placement {

struct Deallocator {
  Void deallocate(Void *) const {}
};


}}} // namespace CShift::LWF::Placement

#endif // CSHIFT_LWF_PLACEMENT_DEALLOCATOR_H
