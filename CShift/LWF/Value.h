#ifndef CSHIFT_LWF_VALUE_H
#define CSHIFT_LWF_VALUE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Move/reference.h"


namespace CShift {
namespace LWF {

template <typename T>
struct Value {

  typedef T Type;
  typedef Type &Reference;
#if PLATFORM_COMPILER_RVALUE_REFERENCE
  struct Rvalue { typedef typename Value::Reference &Reference; };
#endif // C++11
  template <typename Index = Int> struct Ptr;
  template <typename Index = Int> struct Range;
  struct Move {
    template <typename Index = Int> struct Ptr;
    template <typename Index = Int> struct Range;
  };

  struct Predicate {
    struct Equal   { struct To; };
    struct Not     { struct Equal { struct To; }; };
    //struct Greater { struct Than; struct Or { struct { struct Equal { struct To; };};};};
    //struct Less    { struct Than; struct Or { struct { struct Equal { struct To; };};};};
  };

  Void swap(const Value &value) const;
  Void swap(Type &value) const;

  operator Type & () const { return *value; }

  Value(Type  &value_) : value(&value_)       {}
  Value(const Value &value_) : value(value_.value)  {}
  Value  &operator = (const Type  &value) { *this->value = value;        return *this; }
  Value  &operator = (const Value &value) { *this->value = *value.value; return *this; }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Value &operator = (Type &&value) {
    *this->value = (LWF::Forward::reference<Type>(value)); return *this;
  }
  #endif // C++11

  private: Type *value;
};

template <typename Type>
LWF::Value<Type> reference(Type &value) { return value; }

namespace Const {

template <typename T,
          typename Base = const LWF::Value<const T> >
struct Value : Base {
  Value(typename Base::Type &value) : Base(value) {}
  Value(const Value &value) : Base(value)  {}
};

template <typename Type>
LWF::Const::Value<Type> reference(const Type &value) { return value; }

} // namespace Const

#if PLATFORM_COMPILER_RVALUE_REFERENCE
namespace Reference {

template <typename Type>
struct Value {
  Value(Type &value_): value(value_) {}
  operator Type && () const { return LWF::Move::reference(value); }
  private: Type &value;
};

} // namespace Reference
#endif // C++11

}} // namespace CShift::LWF
  
#endif // CSHIFT_LWF_VALUE_H 
