#ifndef CSHIFT_LWF_TRAITS_EXCLUSIVELY_NONFUNDAMENTAL_H
#define CSHIFT_LWF_TRAITS_EXCLUSIVELY_NONFUNDAMENTAL_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Type.h"
#include "LWF/Traits/Construction/Transparency.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Exclusively {

template <typename T, typename Kind = typename LWF::Traits::Type<T>::Kind>
struct Nonfundamental{};

template <typename T>
struct Nonfundamental<T, Platform::Hardware::Type::Kind::Nonfundamental> : T  {
  ConstructionTransparency(Nonfundamental, T){}
};

}}}} // namespace CShift::Traits::Exclusively

#endif // CSHIFT_LWF_TRAITS_EXCLUSIVELY_NONFUNDAMENTAL_H
