#ifndef CSHIFT_LWF_TRAITS_NO_REFERENCE_H
#define CSHIFT_LWF_TRAITS_NO_REFERENCE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace No {

template<typename Type_>
struct Reference          { typedef Type_ Type; };

template<typename Type_>
struct Reference<Type_ &> { typedef typename Reference<Type_>::Type Type; };

}}}} // namespace CShift::LWF::Traits::No

#endif // CSHIFT_LWF_TRAITS_NO_REFERENCE_H
