#ifndef CSHIFT_LWF_TRAITS_UVALUE_PTR_H
#define CSHIFT_LWF_TRAITS_UVALUE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Lvalue/Ptr.h"
#include "LWF/Traits/Rvalue/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Uvalue {

template <typename UType, typename Traits>
struct Reference { typedef Traits Type; };

template <typename UType, typename Traits>
struct Reference<UType&, Traits> { typedef Traits &Type; };

template <typename Base, typename Traits>
struct Ptr {
  struct Return { typedef typename Reference<typename Base::Return::Type, Traits>::Type Type; };
};

}}}} // namespace CShift::LWF::Traits::Uvalue

#endif // CSHIFT_LWF_TRAITS_UVALUE_PTR_H
