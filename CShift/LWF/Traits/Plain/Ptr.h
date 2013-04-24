#ifndef CSHIFT_LWF_TRAITS_PLAIN_PTR_H
#define CSHIFT_LWF_TRAITS_PLAIN_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Plain {

template <typename T, typename TU = T *>
struct Ptr {
  typedef T Type;
  struct Unbiased { typedef TU Type; };
};

}}}} // namespace CShift::LWF::Traits::Plain

#endif // CSHIFT_LWF_TRAITS_PLAIN_PTR_H
