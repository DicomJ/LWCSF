#ifndef CSHIFT_LWF_TRAITS_NONCONST_H
#define CSHIFT_LWF_TRAITS_NONCONST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"


namespace CShift {
namespace LWF {
namespace Traits {

template <typename Base_>
struct Nonconst : Base_ {
  private: typedef Base_ Base; public:
  Nonconst(Base &base) : Base(base) {}
  Nonconst(const Nonconst& nonconst)
    : Base(const_cast<Base &>(static_cast<const Base &>(nonconst))) {}
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_NONCONST_H
