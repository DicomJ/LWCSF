#ifndef CSHIFT_LWF_QUEUE_H
#define CSHIFT_LWF_QUEUE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Ring/Deque.h"

namespace CShift {
namespace LWF {

template <typename Type, typename Base = LWF::Ring::Deque<Type> >
struct Queue : protected Base {

  Bool empty() const { return Base::empty(); }
  UInt size () const { return Base::size (); }

  Type       &front()       { return Base::front(); }
  const Type &front() const { return Base::front(); }

  Type       &back ()       { return Base::back (); }
  const Type &back () const { return Base::back (); }

  Void push(const Type &value) { Base::pushBack(value); }
  Void push(Type &value) { Base::pushBack(value); }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Void push(Type &&value) { Base::pushBack(LWF::Forward::reference<Type>(value)); }
  #endif // !C++11

  Void pop() { Base::popFront(); }

  Queue() {}
  ConstructionTransparency(Queue, Base) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_QUEUE_H
