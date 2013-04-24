#ifndef CSHIFT_LWF_VALUE_MOVE_RANGE_H
#define CSHIFT_LWF_VALUE_MOVE_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value/Move/Ptr.h"


namespace CShift {
namespace LWF {

template <typename Type>
template <typename Index>
struct Value<Type>::Move::Range : LWF::Range<LWF::Value<Type>::Move::Ptr<Index> > {
  Range(Type *value, Index index, UInt count) :
    LWF::Range<typename LWF::Value<Type>::Move::template Ptr<Index> > (
      typename LWF::Value<Type>::Move::template Ptr<Index>(value, index),
      typename LWF::Value<Type>::Move::template Ptr<Index>(value, index + count)) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VALUE_MOVE_RANGE_H
