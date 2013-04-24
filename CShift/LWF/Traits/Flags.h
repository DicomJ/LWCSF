#ifndef CSHIFT_LWF_TRAITS_FLAGS_H
#define CSHIFT_LWF_TRAITS_FLAGS_H

#include "LWF/License"
#include "Author/Andriy.Bulka"
#include "LWF/Integer.h"

#include "LWF/Traits/Enum.h"

namespace CShift {
namespace LWF {
namespace Traits {

template <UInt bytes = LWF::Type<UInt>::size>
struct Flags : LWF::Traits::Enum<typename LWF::Integer<bytes>::Type> {

  private: typedef LWF::Traits::Enum<typename LWF::Integer<bytes>::Type> Base; public:

  Flags(typename Base::Type flags) : Base(flags) {}

  Bool operator & (typename Base::Type flags) const {
    return (static_cast<const Base &>(*this) & flags) != 0;
  }
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_FLAGS_H
