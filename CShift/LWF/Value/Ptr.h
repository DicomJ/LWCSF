#ifndef CSHIFT_LWF_VALUE_PTR_H
#define CSHIFT_LWF_VALUE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value.h"
#include "LWF/Traits/Value/Ptr.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {

template <typename Type>
template <typename Index>
struct Value<Type>::Ptr
    : LWF::Ptr< LWF::Traits::Value::Ptr<LWF::Weak::Ptr<Type>, Index> > {
  private: typedef LWF::Weak::Ptr<Type> Traits;
  public : typedef LWF::Ptr< LWF::Traits::Value::Ptr<Traits, Index> > Base;
  public : 

  Ptr(Type *value, Index index = 0) : Base(Traits(value), index) {}

  Ptr(const Null & = null) : Base(Traits(null), 0) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Base &ptr) : Base(ptr) {} // ptr = ptr + 1
  Ptr &operator = (const Base &ptr) { Base::operator = (ptr); return *this; }
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_VALUE_PTR_H
