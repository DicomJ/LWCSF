#ifndef CSHIFT_LWF_TRAITS_COMPOSITOR_H
#define CSHIFT_LWF_TRAITS_COMPOSITOR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Move/reference.h"
#include "LWF/Forward/reference.h"


namespace CShift {
namespace LWF {
namespace Traits {

template <typename Type, typename = typename LWF::Type<Type>::Kind >
struct Compositor {
  Compositor(const Type &value_) : value(value_) {}
  Compositor &operator = (const Type &value) { this->value = value; return *this; }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Compositor(Compositor &&value_) : value(LWF::Move::reference(value_.value)) {}
  Compositor &operator = (Compositor &&value)  {
    this->value = LWF::Move::reference(value.value); return *this;
  }

  Compositor(Type &&value_) : value(LWF::Forward::reference<Type>(value_)) {}
  Compositor &operator = (Type &&value) {
    this->value = LWF::Forward::reference<Type>(value); return *this;
  }
  #endif // C++11

  operator Type & () { return value; }
  operator const Type & () const { return value; }

  private: Type value;
};

template <typename Type>
struct Compositor<Type, LWF::Kind::Nonfundamental>: Type {

  Compositor(const Type &value) : Type(value) {}

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Compositor(Type &&value) : Type(LWF::Forward::reference<Type>(value)) {}
  Compositor(Compositor &&value) : Type(LWF::Forward::reference<Type>(value)) {}
  #endif // C++11
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_COMPOSITOR_H
