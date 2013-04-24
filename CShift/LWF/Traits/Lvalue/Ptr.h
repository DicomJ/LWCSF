#ifndef CSHIFT_LWF_TRAITS_LVALUE_PTR_H
#define CSHIFT_LWF_TRAITS_LVALUE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Lvalue {

template <typename Base>
struct Ptr : Base {
  struct Return { typedef typename Base::Type &Type; };
};

}}}} // namespace CShift::LWF::Traits::Lvalue

#endif // CSHIFT_LWF_TRAITS_LVALUE_PTR_H
