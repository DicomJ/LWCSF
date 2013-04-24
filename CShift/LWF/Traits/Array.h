#ifndef CSHIFT_LWF_TRAITS_ARRAY_H
#define CSHIFT_LWF_TRAITS_ARRAY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"
#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Forward/reference.h"
#include "LWF/Move/reference.h"


namespace CShift {
namespace LWF {
namespace Traits {

template <typename Begin>
struct Array {

  typedef typename Begin::Type Type;
  typedef typename LWF::Weak::Ptr<Type[]> Iterator;

  Iterator begin() const { return begin_; }
  Iterator end() const { return end_; }

  Bool operator == (const Null &) const { return begin() == null; }
  Array &operator = (const Null &) { begin_ = null; end_ = null; return *this; }

  Array(const Begin  &begin, const Iterator &end) : begin_(begin), end_(end) {}
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(      Begin &&begin, const Iterator &end) : begin_(begin), end_(end) {}
  #else  // !C++11
  Array(      Begin  &begin, const Iterator &end) : begin_(begin), end_(end) {}
  #endif // !C++11

  Array(const Array &array) : begin_(array.begin_), end_(array.end_) {}
  Array &operator = (const Array &array) {
    begin_ = array.begin_; end_ = array.end_; return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Array(Array &&array) : begin_(LWF::Move::reference(array.begin_))
                       , end_  (LWF::Move::reference(array.end_  )) {
    array.end_ = array.begin_;
  }
  Array &operator = (Array &&array) {
    begin_= LWF::Move::reference(array.begin_);
    end_  = LWF::Move::reference(array.end_  );
    array.end_ = array.begin_;
    return *this;
  }
  #endif // C++11
  Array(Array &array) : begin_(array.begin_), end_(array.end_) {
    array.end_ = array.begin_;
  }
  Array &operator = (Array &array) {
    begin_= array.begin_;
    end_  = array.end_  ;
    array.end_ = array.begin_;
    return *this;
  }

  protected: Begin begin_;
  protected: Iterator end_;
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_ARRAY_H
