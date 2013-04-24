#ifndef CSHIFT_LWF_VALUE_PREDICATE_EQUAL_TO_H
#define CSHIFT_LWF_VALUE_PREDICATE_EQUAL_TO_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value.h"


namespace CShift {
namespace LWF {
  
template <typename Type>
struct Value<Type>::Predicate::Equal::To : LWF::Value<Type>
{
  To(Type &value) : Value(value){}

  Bool operator() (Type &value) const { return *this == value; }
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VALUE_PREDICATE_EQUAL_TO_H
