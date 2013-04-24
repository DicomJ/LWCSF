#ifndef CSHIFT_LWF_STATIC_TRAITS_ARRAY_H
#define CSHIFT_LWF_STATIC_TRAITS_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {
namespace Static {
namespace Traits {

template <typename Begin, UInt size>
struct Array {

  typedef typename LWF::Weak::Ptr<typename Begin::Type[]> Iterator;

  static const UInt amount = size;

  Iterator begin() const { return begin_; }
  Iterator end() const { return begin() != null ? begin() + size : null; }

  Bool operator == (const Null &) const { return begin() == null; }
  Array &operator = (const Null &) { begin_ = null; return *this; }

  Array(const Begin  &begin) : begin_(begin) {}
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(      Begin &&begin) : begin_(begin) {}
  #else  // !C++11
  Array(      Begin  &begin) : begin_(begin) {}
  #endif // !C++11

  protected: Begin begin_;
};

template <typename Begin>
struct Array<Begin, 0> : LWF::Traits::Prototype {};

}}}} // namespace CShift::LWF::Static::Traits

#endif // CSHIFT_LWF_STATIC_TRAITS_ARRAY_H
