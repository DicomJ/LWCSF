#ifndef CSHIFT_LWF_STACK_H
#define CSHIFT_LWF_STACK_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Deque.h"


namespace CShift {
namespace LWF {

template <typename Type, typename Base = LWF::Deque<Type> >
struct Stack : protected Base {

  Bool empty() const { return Base::empty(); }
  UInt size () const { return Base::size (); }

  Type       &top()       { return Base::front(); }
  const Type &top() const { return Base::front(); }

  Void push(const Type &value) { Base::pushFront(value); }
  Void push(Type &value) { Base::pushFront(value); }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Void push(Type &&value) { Base::pushFront(LWF::Forward::reference<Type>(value); }
  #endif // !C++11

  Void pop() { Base::popFront(); }

  Stack() {}
  ConstructionTransparency(Stack, Base) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_STACK_H
