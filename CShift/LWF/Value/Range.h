#ifndef CSHIFT_LWF_VALUE_RANGE_H
#define CSHIFT_LWF_VALUE_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value/Ptr.h"


namespace CShift {
namespace LWF {

template <typename Type>
template <typename Index>
struct Value<Type>::Range : LWF::Range<LWF::Value<Type>::Ptr<Index> > {
  Range(Type *value, Index index, UInt count) :
    LWF::Range<typename LWF::Value<Type>::template Ptr<Index> > (
      typename LWF::Value<Type>::template Ptr<Index>(value, index),
      typename LWF::Value<Type>::template Ptr<Index>(value, index + count)) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VALUE_RANGE_H
