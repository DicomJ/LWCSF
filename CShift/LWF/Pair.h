#ifndef CSHIFT_LWF_PAIR_H
#define CSHIFT_LWF_PAIR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Tuple.h"


namespace CShift {
namespace LWF {

template <typename T0, typename T1>
struct Pair : LWF::Tuple<T0, T1> {
 private: typedef LWF::Tuple<T0, T1> Base; public:

  template <UInt index>
  struct Item {
    typedef typename Base::template Index<index>::Arg::Type Type;
    typedef typename Base::template Index<index>::Arg::Reference Reference;
    #if PLATFORM_COMPILER_RVALUE_REFERENCE
    struct Rvalue {  typedef typename
      Base::template Index<index>::Arg::Rvalue::Reference Reference;
    };
    #endif
  };

  struct First  : Item<0> {};
  struct Second : Item<1> {};

  const typename First::Type &first() const { return Base::template at<0>(); }
  typename First::Type &first() { return Base::template at<0>(); }

  const typename Second::Type &second() const { return Base::template at<1>(); }
  typename Second::Type &second() { return Base::template at<1>(); }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Pair(typename First::Rvalue::Reference first,
       typename Second::Rvalue::Reference second) : Base(first, second) {}
  #else
  Pair(typename First::Reference first,
       typename Second::Reference second) : Base(first, second){}
  #endif // !C++11

  #if PLATFORM_COMPILER_RVALUE_REFERENCE

  Pair(Pair &&pair) : Base(LWF::Forward::reference<Base>(pair)) {}
  Pair(Base &&base) : Base(LWF::Forward::reference<Base>(base)) {}

  template <typename U0, typename U1>
  Pair(Pair<U0, U1> &&pair)
    : Base(LWF::Forward::reference<Pair<U0, U1> >(pair)) {}
  template <typename U0, typename U1>
  Pair(LWF::Tuple<U0, U1> &&base)
    : Base(LWF::Forward::reference<LWF::Tuple<U0, U1> >(base)) {}

  #endif // C++11

  Pair(const Pair &pair) : Base(pair) {}
  Pair(const Base &base) : Base(base) {}

  template <typename U0, typename U1>
  Pair(const Pair<U0, U1> &pair) : Base(pair) {}
  template <typename U0, typename U1>
  Pair(const LWF::Tuple<U0, U1> &base) : Base(base) {}
};

#if PLATFORM_COMPILER_RVALUE_REFERENCE
template <typename First, typename Second>
Pair<First, Second>
pair(First &&first, Second &&second) {
  return Pair<First, Second>(first, second);
}
#endif //C++11

template <typename First, typename Second>
Pair<First, Second>
pair(const First &first, const Second &second) {
  return Pair<First, Second>(first, second);
}


}} // namespace CShift::LWF

#endif // CSHIFT_LWF_PAIR_H
