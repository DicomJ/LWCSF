#ifndef CSHIFT_LWF_TRAITS_PTR_H
#define CSHIFT_LWF_TRAITS_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Construction/Transparency.h"
#include "LWF/Traits/Uvalue/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {

template <typename Base>
struct Ptr : Base {
#define PtrConstructionTransparency() ConstructionTransparency(Ptr, Base)
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_PTR_H
