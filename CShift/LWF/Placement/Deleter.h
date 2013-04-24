#ifndef CSHIFT_LWF_PLACEMENT_DELETER_H
#define CSHIFT_LWF_PLACEMENT_DELETER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Destroying/Deleter.h"


namespace CShift {
namespace LWF {
namespace Placement {

template <typename T,
          typename Deallocator = LWF::Placement::Deallocator,
          typename Base = LWF::Destroying::Deleter<T, Deallocator> >
struct Deleter : Base {
  Deleter(const Deallocator &deallocator = Deallocator()) : Base(deallocator) {}
};

}}} // namespace CShift::LWF::Placement

#endif // CSHIFT_LWF_PLACEMENT_DELETER_H
