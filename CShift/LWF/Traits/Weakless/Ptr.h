#ifndef CSHIFT_LWF_TRAITS_WEAKLESS_PTR_H
#define CSHIFT_LWF_TRAITS_WEAKLESS_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Weakness/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Weakless {

template <typename Traits>
struct Ptr : Weakness::Ptr<Traits> {
  private: typedef Weakness::Ptr<Traits> Base; public:

  static const Bool weakness = False;
  PtrConstructionTransparency() {}

  private: Int operator - (const Ptr &ptr) const;
  private: Ptr operator + (Int index) const;
};

}}}} // namespace CShift::LWF::Traits::Weakless

#endif // CSHIFT_LWF_TRAITS_WEAKLESS_PTR_H
