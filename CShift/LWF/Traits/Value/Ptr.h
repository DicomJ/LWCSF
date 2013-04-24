#ifndef CSHIFT_LWF_TRAITS_VALUE_PTR_H
#define CSHIFT_LWF_TRAITS_VALUE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Index/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Value {

template <typename Traits, typename Index_>
struct Ptr : LWF::Index::Ptr<Index_> {
  private: typedef LWF::Index::Ptr<Index_> Base; public:
  typedef typename Traits::Type Type;
  struct Return { typedef typename Traits::Return::Type Type; };
  struct Index { typedef Index_ Type; };

  typename Return::Type operator * () const { return *value; }
  Ptr operator + (Int index) const { return Ptr(value, *Base::operator + (index)); }

  Ptr(const Traits &value_, typename Index::Type index) : Base(index), value(value_) {}

  private: Traits value;
};

}}}} // namespace CShift::LWF::Tratis::Value

#endif // CSHIFT_LWF_TRAITS_VALUE_PTR_H
