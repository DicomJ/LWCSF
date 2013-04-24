#ifndef CSHIFT_LWF_TUPLE_H
#define CSHIFT_LWF_TUPLE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Null.h"
#include "LWF/Value.h"
#include "LWF/Traits/Compositor.h"
#include "LWF/Move/reference.h"
#include "LWF/Forward/reference.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Algorithm/swap.h"

// A non-recursive implementation is easy to compile
// and is a bit more human understandable!!!


namespace CShift {
namespace LWF {

namespace Traits {
namespace Tuple {

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
struct Types {

  template <UInt index, typename T>
  struct Arg : LWF::Traits::Compositor<T> {
    private: typedef LWF::Traits::Compositor<T> Base; public:
    typedef T Type;
    typedef const Type &Reference;
    #if PLATFORM_COMPILER_RVALUE_REFERENCE
    struct Rvalue { typedef typename Arg::Reference &Reference; };
    #endif // C++11

    Arg(const Type &arg) : Base(arg) {}
    Arg &operator = (const Type &arg) { Base::operator = (arg); return *this; }

    #if PLATFORM_COMPILER_RVALUE_REFERENCE
    Arg(Arg &&arg) : Base(LWF::Forward::reference<Base>(arg)) {}
    Arg &operator = (Arg &&arg) {
      Base::operator = (LWF::Forward::reference<Base>(arg)); return *this;
    }
    #endif // C++11
  };

  template <UInt index>
  struct Arg<index, Null> : Null {
    typedef const Null &Reference;
    struct Rvalue { typedef typename Arg::Reference Reference; };

    Arg(const Null&) {}
  };

  template <UInt index, typename T>
  struct Arg<index, T &> : LWF::Value<T> {
    private: typedef LWF::Value<T> Base; public:

    Arg(const Base &arg) : Base(arg) {}
    Arg &operator = (const Base &arg) { Base::operator = (arg); return *this; }

    Arg(T &arg) : Base(arg) {}
    Arg  &operator = (const T &arg) { Base::operator = (arg); return *this; }
  };

  template <UInt index, typename T>
  struct Arg<index, const T &> : LWF::Const::Value<T> {
    private: typedef LWF::Const::Value<T> Base; public:
    Arg(const T &arg) : Base(arg) {}
    Arg(const Base &arg) : Base(arg) {}
  };

  template <UInt index, typename T>
  struct Arg<index, LWF::Value<T> > : LWF::Value<T> {
    private: typedef LWF::Value<T> Base; public:

    Arg(T &arg) : Base(arg) {}
    Arg(const Base &arg) : Base(arg) {}

    Arg &operator = (const Base &arg) { Base::operator = (arg); return *this; }
    Arg  &operator = (const T &arg) { Base::operator = (arg); return *this; }
  };

  template <UInt index, typename T>
  struct Arg<index, LWF::Const::Value<T> > : LWF::Const::Value<T> {
    private: typedef LWF::Const::Value<T> Base; public:
    Arg(const T &arg) : Base(arg) {}
    Arg(const Base &arg) : Base(arg) {}
  };

  template <UInt index, typename = Void> struct Index;
  template <typename _> struct Index<0, _> { typedef Types::Arg<0, T0> Arg; };
  template <typename _> struct Index<1, _> { typedef Types::Arg<1, T1> Arg; };
  template <typename _> struct Index<2, _> { typedef Types::Arg<2, T2> Arg; };
  template <typename _> struct Index<3, _> { typedef Types::Arg<3, T3> Arg; };
  template <typename _> struct Index<4, _> { typedef Types::Arg<4, T4> Arg; };
  template <typename _> struct Index<5, _> { typedef Types::Arg<5, T5> Arg; };
  template <typename _> struct Index<6, _> { typedef Types::Arg<6, T6> Arg; };
  template <typename _> struct Index<7, _> { typedef Types::Arg<7, T7> Arg; };
  template <typename _> struct Index<8, _> { typedef Types::Arg<8, T8> Arg; };
  template <typename _> struct Index<9, _> { typedef Types::Arg<9, T9> Arg; };
};

}} // namespace Traits::Tuple


template <typename T0 = Null, typename T1 = Null,
          typename T2 = Null, typename T3 = Null,
          typename T4 = Null, typename T5 = Null,
          typename T6 = Null, typename T7 = Null,
          typename T8 = Null, typename T9 = Null,
          typename Types = Traits::Tuple::Types<T0, T1, T2, T3, T4,
                                                T5, T6, T7, T8, T9> >
struct Tuple : Types::template Index<0>::Arg, Types::template Index<1>::Arg,
               Types::template Index<2>::Arg, Types::template Index<3>::Arg,
               Types::template Index<4>::Arg, Types::template Index<5>::Arg,
               Types::template Index<6>::Arg, Types::template Index<7>::Arg,
               Types::template Index<8>::Arg, Types::template Index<9>::Arg {

  template <UInt index> struct Index : Types::template Index<index> {};

  struct Is {
    template<UInt index>
    struct Index {
      static const Bool null =
          LWF::Type<typename Tuple::template Index<index>::Arg>::Is::Equal
            ::template To<typename Types::template Arg<index, Null> >::type;
    };
  };

#if PLATFORM_COMPILER_RVALUE_REFERENCE
  Tuple(typename Index<0>::Arg::Rvalue::Reference a0 = null,
        typename Index<1>::Arg::Rvalue::Reference a1 = null,
        typename Index<2>::Arg::Rvalue::Reference a2 = null,
        typename Index<3>::Arg::Rvalue::Reference a3 = null,
        typename Index<4>::Arg::Rvalue::Reference a4 = null,
        typename Index<5>::Arg::Rvalue::Reference a5 = null,
        typename Index<6>::Arg::Rvalue::Reference a6 = null,
        typename Index<7>::Arg::Rvalue::Reference a7 = null,
        typename Index<8>::Arg::Rvalue::Reference a8 = null,
        typename Index<9>::Arg::Rvalue::Reference a9 = null)
    : Index<0>::Arg(LWF::Forward::reference<typename Index<0>::Arg::Rvalue::Reference>(a0)),
      Index<1>::Arg(LWF::Forward::reference<typename Index<1>::Arg::Rvalue::Reference>(a1)),
      Index<2>::Arg(LWF::Forward::reference<typename Index<2>::Arg::Rvalue::Reference>(a2)),
      Index<3>::Arg(LWF::Forward::reference<typename Index<3>::Arg::Rvalue::Reference>(a3)),
      Index<4>::Arg(LWF::Forward::reference<typename Index<4>::Arg::Rvalue::Reference>(a4)),
      Index<5>::Arg(LWF::Forward::reference<typename Index<5>::Arg::Rvalue::Reference>(a5)),
      Index<6>::Arg(LWF::Forward::reference<typename Index<6>::Arg::Rvalue::Reference>(a6)),
      Index<7>::Arg(LWF::Forward::reference<typename Index<7>::Arg::Rvalue::Reference>(a7)),
      Index<8>::Arg(LWF::Forward::reference<typename Index<8>::Arg::Rvalue::Reference>(a8)),
      Index<9>::Arg(LWF::Forward::reference<typename Index<9>::Arg::Rvalue::Reference>(a9)) {}
#else
  Tuple(typename Index<0>::Arg::Reference a0 = null,
        typename Index<1>::Arg::Reference a1 = null,
        typename Index<2>::Arg::Reference a2 = null,
        typename Index<3>::Arg::Reference a3 = null,
        typename Index<4>::Arg::Reference a4 = null,
        typename Index<5>::Arg::Reference a5 = null,
        typename Index<6>::Arg::Reference a6 = null,
        typename Index<7>::Arg::Reference a7 = null,
        typename Index<8>::Arg::Reference a8 = null,
        typename Index<9>::Arg::Reference a9 = null)
    : Index<0>::Arg(a0), Index<1>::Arg(a1),
      Index<2>::Arg(a2), Index<3>::Arg(a3),
      Index<4>::Arg(a4), Index<5>::Arg(a5),
      Index<6>::Arg(a6), Index<7>::Arg(a7),
      Index<8>::Arg(a8), Index<9>::Arg(a9) {}
#endif

#if 1
  Tuple(const Tuple &t) :
    Index<0>::Arg(static_cast<const typename Index<0>::Arg &>(t)),
    Index<1>::Arg(static_cast<const typename Index<1>::Arg &>(t)),
    Index<2>::Arg(static_cast<const typename Index<2>::Arg &>(t)),
    Index<3>::Arg(static_cast<const typename Index<3>::Arg &>(t)),
    Index<4>::Arg(static_cast<const typename Index<4>::Arg &>(t)),
    Index<5>::Arg(static_cast<const typename Index<5>::Arg &>(t)),
    Index<6>::Arg(static_cast<const typename Index<6>::Arg &>(t)),
    Index<7>::Arg(static_cast<const typename Index<7>::Arg &>(t)),
    Index<8>::Arg(static_cast<const typename Index<8>::Arg &>(t)),
    Index<9>::Arg(static_cast<const typename Index<9>::Arg &>(t)) {}

  Tuple &operator = (const Tuple &t) {
    Index<0>::Arg::operator = (static_cast<const typename Index<0>::Arg &>(t));
    Index<1>::Arg::operator = (static_cast<const typename Index<1>::Arg &>(t));
    Index<2>::Arg::operator = (static_cast<const typename Index<2>::Arg &>(t));
    Index<3>::Arg::operator = (static_cast<const typename Index<3>::Arg &>(t));
    Index<4>::Arg::operator = (static_cast<const typename Index<4>::Arg &>(t));
    Index<5>::Arg::operator = (static_cast<const typename Index<5>::Arg &>(t));
    Index<6>::Arg::operator = (static_cast<const typename Index<6>::Arg &>(t));
    Index<7>::Arg::operator = (static_cast<const typename Index<7>::Arg &>(t));
    Index<8>::Arg::operator = (static_cast<const typename Index<8>::Arg &>(t));
    Index<9>::Arg::operator = (static_cast<const typename Index<9>::Arg &>(t));
    return *this;
  }
#endif
  template <typename U0, typename U1, typename U2, typename U3, typename U4,
            typename U5, typename U6, typename U7, typename U8, typename U9>
  Tuple(const Tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &t)
    : Index<0>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<0>::Arg &>(t)),
      Index<1>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<1>::Arg &>(t)),
      Index<2>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<2>::Arg &>(t)),
      Index<3>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<3>::Arg &>(t)),
      Index<4>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<4>::Arg &>(t)),
      Index<5>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<5>::Arg &>(t)),
      Index<6>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<6>::Arg &>(t)),
      Index<7>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<7>::Arg &>(t)),
      Index<8>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<8>::Arg &>(t)),
      Index<9>::Arg(static_cast<const typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<9>::Arg &>(t)) {
  }

  template <typename U0, typename U1, typename U2, typename U3, typename U4,
            typename U5, typename U6, typename U7, typename U8, typename U9>
  Tuple &operator = (const Tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &t) {
    typedef Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9> TupleU;
    static_cast<typename Index<0>::Arg>(*this) = static_cast<const typename TupleU::template Index<0>::Arg &>(t);
    static_cast<typename Index<1>::Arg>(*this) = static_cast<const typename TupleU::template Index<1>::Arg &>(t);
    static_cast<typename Index<2>::Arg>(*this) = static_cast<const typename TupleU::template Index<2>::Arg &>(t);
    static_cast<typename Index<3>::Arg>(*this) = static_cast<const typename TupleU::template Index<3>::Arg &>(t);
    static_cast<typename Index<4>::Arg>(*this) = static_cast<const typename TupleU::template Index<4>::Arg &>(t);
    static_cast<typename Index<5>::Arg>(*this) = static_cast<const typename TupleU::template Index<5>::Arg &>(t);
    static_cast<typename Index<6>::Arg>(*this) = static_cast<const typename TupleU::template Index<6>::Arg &>(t);
    static_cast<typename Index<7>::Arg>(*this) = static_cast<const typename TupleU::template Index<7>::Arg &>(t);
    static_cast<typename Index<8>::Arg>(*this) = static_cast<const typename TupleU::template Index<8>::Arg &>(t);
    static_cast<typename Index<9>::Arg>(*this) = static_cast<const typename TupleU::template Index<9>::Arg &>(t);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
#if 1
  Tuple(Tuple &&t) :
    Index<0>::Arg(LWF::Forward::reference<typename Index<0>::Arg>(t)),
    Index<1>::Arg(LWF::Forward::reference<typename Index<1>::Arg>(t)),
    Index<2>::Arg(LWF::Forward::reference<typename Index<2>::Arg>(t)),
    Index<3>::Arg(LWF::Forward::reference<typename Index<3>::Arg>(t)),
    Index<4>::Arg(LWF::Forward::reference<typename Index<4>::Arg>(t)),
    Index<5>::Arg(LWF::Forward::reference<typename Index<5>::Arg>(t)),
    Index<6>::Arg(LWF::Forward::reference<typename Index<6>::Arg>(t)),
    Index<7>::Arg(LWF::Forward::reference<typename Index<7>::Arg>(t)),
    Index<8>::Arg(LWF::Forward::reference<typename Index<8>::Arg>(t)),
    Index<9>::Arg(LWF::Forward::reference<typename Index<9>::Arg>(t)) {}

  Tuple &operator = (Tuple &&t) {
    Index<0>::Arg::operator = (LWF::Forward::reference<typename Index<0>::Arg>(t));
    Index<1>::Arg::operator = (LWF::Forward::reference<typename Index<1>::Arg>(t));
    Index<2>::Arg::operator = (LWF::Forward::reference<typename Index<2>::Arg>(t));
    Index<3>::Arg::operator = (LWF::Forward::reference<typename Index<3>::Arg>(t));
    Index<4>::Arg::operator = (LWF::Forward::reference<typename Index<4>::Arg>(t));
    Index<5>::Arg::operator = (LWF::Forward::reference<typename Index<5>::Arg>(t));
    Index<6>::Arg::operator = (LWF::Forward::reference<typename Index<6>::Arg>(t));
    Index<7>::Arg::operator = (LWF::Forward::reference<typename Index<7>::Arg>(t));
    Index<8>::Arg::operator = (LWF::Forward::reference<typename Index<8>::Arg>(t));
    Index<9>::Arg::operator = (LWF::Forward::reference<typename Index<9>::Arg>(t));
    return *this;
  }
#endif
  template <typename U0, typename U1, typename U2, typename U3, typename U4,
            typename U5, typename U6, typename U7, typename U8, typename U9>
  Tuple(Tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &&t)
    : Index<0>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<0>::Arg>(t)),
      Index<1>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<1>::Arg>(t)),
      Index<2>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<2>::Arg>(t)),
      Index<3>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<3>::Arg>(t)),
      Index<4>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<4>::Arg>(t)),
      Index<5>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<5>::Arg>(t)),
      Index<6>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<6>::Arg>(t)),
      Index<7>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<7>::Arg>(t)),
      Index<8>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<8>::Arg>(t)),
      Index<9>::Arg(LWF::Forward::reference<typename Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9>::template Index<9>::Arg>(t)) {}

  template <typename U0, typename U1, typename U2, typename U3, typename U4,
            typename U5, typename U6, typename U7, typename U8, typename U9>
  Tuple &operator = (Tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> &&t) {
    typedef Tuple<U0,U1,U2,U3,U4,U5,U6,U7,U8,U9> TupleU;
    static_cast<typename Index<0>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<0>::Arg>(t);
    static_cast<typename Index<1>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<1>::Arg>(t);
    static_cast<typename Index<2>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<2>::Arg>(t);
    static_cast<typename Index<3>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<3>::Arg>(t);
    static_cast<typename Index<4>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<4>::Arg>(t);
    static_cast<typename Index<5>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<5>::Arg>(t);
    static_cast<typename Index<6>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<6>::Arg>(t);
    static_cast<typename Index<7>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<7>::Arg>(t);
    static_cast<typename Index<8>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<8>::Arg>(t);
    static_cast<typename Index<9>::Arg>(*this) = LWF::Forward::reference<typename TupleU::template Index<9>::Arg>(t);
    return *this;
  }
  #endif // C++11

  template <UInt index>
  typename Index<index>::Arg::Type & at() {
    return static_cast<typename Index<index>::Arg &>(*this);
  }
  template <UInt index>
  const typename Index<index>::Arg::Type & at() const {
    return static_cast<const typename Index<index>::Arg &>(*this);
  }

  Int difference(const Tuple &t) const { Int n = 0; return
    (0 == (n = difference<0>(t)) && 0 == (n = difference<1>(t)) &&
     0 == (n = difference<2>(t)) && 0 == (n = difference<3>(t)) &&
     0 == (n = difference<4>(t)) && 0 == (n = difference<5>(t)) &&
     0 == (n = difference<6>(t)) && 0 == (n = difference<7>(t)) &&
     0 == (n = difference<8>(t)) && 0 == (n = difference<9>(t))), n;
  }
  Bool operator >= (const Tuple &t) { return difference(t) >= 0; }
  Bool operator <= (const Tuple &t) { return difference(t) <= 0; }
  Bool operator <  (const Tuple &t) { return difference(t) <  0; }
  Bool operator >  (const Tuple &t) { return difference(t) >  0; }


  Bool equal(const Tuple &t) const { return
    equal<0>(t) && equal<1>(t) && equal<2>(t) && equal<3>(t) && equal<4>(t) &&
    equal<5>(t) && equal<6>(t) && equal<7>(t) && equal<8>(t) && equal<9>(t);
  }
  Bool operator == (const Tuple &t) const { return  equal(t); }
  Bool operator != (const Tuple &t) const { return !equal(t); }

  Void swap(Tuple &t) {
    swap<0>(t); swap<1>(t); swap<2>(t); swap<3>(t); swap<4>(t);
    swap<5>(t); swap<6>(t); swap<7>(t); swap<8>(t); swap<9>(t);
  }

  private: template<UInt index>
  Int difference(const Tuple &,
                 typename LWF::Traits::Prediction<
                          Is::template Index<index>::null>::Type * = 0) const {
    return 0;
  }
  private: template<UInt index>
  Int difference(const Tuple &t,
                 typename LWF::Traits::Prediction<
                          !Is::template Index<index>::null>::Type * = 0) const {
    return at<index>() - t.at<index>();
  }
  private: template<UInt index>
  Bool equal(const Tuple &,
             typename LWF::Traits::Prediction<
                          Is::template Index<index>::null>::Type * = 0) const {
    return True;
  }
  private: template<UInt index>
  Bool equal(const Tuple &t,
             typename LWF::Traits::Prediction<
                          !Is::template Index<index>::null>::Type * = 0) const {
    return at<index>() == t.at<index>();
  }

  private: template<UInt index>
  Void swap(Tuple &,
            typename LWF::Traits::Prediction<
                          Is::template Index<index>::null>::Type * = 0) {}
  private: template<UInt index>
  Void swap(Tuple &t,
            typename LWF::Traits::Prediction<
                          !Is::template Index<index>::null>::Type * = 0) {
    LWF::swap(at<index>(), t.at<index>());
  }
};

#if PLATFORM_COMPILER_RVALUE_REFERENCE

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4,
      T5 &&a5, T6 &&a6, T7 &&a7, T8 &&a8, T9 &&a9) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4,
      T5 &&a5, T6 &&a6, T7 &&a7, T8 &&a8) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4,
      T5 &&a5, T6 &&a6, T7 &&a7) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7>
              (a0, a1, a2, a3, a4, a5, a6, a7);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
Tuple<T0, T1, T2, T3, T4, T5, T6>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4,
      T5 &&a5, T6 &&a6) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6>
              (a0, a1, a2, a3, a4, a5, a6);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5>
Tuple<T0, T1, T2, T3, T4, T5>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4,
      T5 &&a5) {
  return Tuple<T0, T1, T2, T3, T4, T5>
              (a0, a1, a2, a3, a4, a5);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4>
Tuple<T0, T1, T2, T3, T4>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3, T4 &&a4) {
  return Tuple<T0, T1, T2, T3, T4>(a0, a1, a2, a3, a4);
}
template <typename T0, typename T1, typename T2, typename T3>
Tuple<T0, T1, T2, T3>
tuple(T0 &&a0, T1 &&a1, T2 &&a2, T3 &&a3) {
  return Tuple<T0, T1, T2, T3>(a0, a1, a2, a3);
}
template <typename T0, typename T1, typename T2>
Tuple<T0, T1, T2>
tuple(T0 &&a0, T1 &&a1, T2 &&a2) {
  return Tuple<T0, T1, T2>(a0, a1, a2);
}
template <typename T0, typename T1>
Tuple<T0, T1>
tuple(T0 &&a0, T1 &&a1) {
  return Tuple<T0, T1>(a0, a1);
}
template <typename T0>
Tuple<T0>
tuple(T0 &&a0) {
  return Tuple<T0>(a0);
}

#endif// C++11

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4,
      const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8, const T9 &a9) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4,
      const T5 &a5, const T6 &a6, const T7 &a7, const T8 &a8) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7>
Tuple<T0, T1, T2, T3, T4, T5, T6, T7>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4,
      const T5 &a5, const T6 &a6, const T7 &a7) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6, T7>
              (a0, a1, a2, a3, a4, a5, a6, a7);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
Tuple<T0, T1, T2, T3, T4, T5, T6>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4,
      const T5 &a5, const T6 &a6) {
  return Tuple<T0, T1, T2, T3, T4, T5, T6>
              (a0, a1, a2, a3, a4, a5, a6);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5>
Tuple<T0, T1, T2, T3, T4, T5>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4,
      const T5 &a5) {
  return Tuple<T0, T1, T2, T3, T4, T5>
              (a0, a1, a2, a3, a4, a5);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4>
Tuple<T0, T1, T2, T3, T4>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3, const T4 &a4) {
  return Tuple<T0, T1, T2, T3, T4>(a0, a1, a2, a3, a4);
}
template <typename T0, typename T1, typename T2, typename T3>
Tuple<T0, T1, T2, T3>
tuple(const T0 &a0, const T1 &a1, const T2 &a2, const T3 &a3) {
  return Tuple<T0, T1, T2, T3>(a0, a1, a2, a3);
}
template <typename T0, typename T1, typename T2>
Tuple<T0, T1, T2>
tuple(const T0 &a0, const T1 &a1, const T2 &a2) {
  return Tuple<T0, T1, T2>(a0, a1, a2);
}
template <typename T0, typename T1>
Tuple<T0, T1>
tuple(const T0 &a0, const T1 &a1) {
  return Tuple<T0, T1>(a0, a1);
}
template <typename T0>
Tuple<T0>
tuple(const T0 &a0) {
  return Tuple<T0>(a0);
}
inline
Tuple<>
tuple() {
  return Tuple<>();
}

template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8, typename T9>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &, T8 &, T9 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4,
    T5 &a5, T6 &a6, T7 &a7, T8 &a8, T9 &a9) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &, T8 &, T9 &>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7, typename T8>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &, T8 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7, T8 &a8) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &, T8 &>
              (a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6, typename T7>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6, T7 &a7) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &, T7 &>
              (a0, a1, a2, a3, a4, a5, a6, a7);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5, typename T6>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5, T6 &a6) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &, T6 &>
              (a0, a1, a2, a3, a4, a5, a6);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4,
          typename T5>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4, T5 &a5) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &, T5 &>(a0, a1, a2, a3, a4, a5);
}
template <typename T0, typename T1, typename T2, typename T3, typename T4>
Tuple<T0 &, T1 &, T2 &, T3 &, T4 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3, T4 &a4) {
  return Tuple<T0 &, T1 &, T2 &, T3 &, T4 &>(a0, a1, a2, a3, a4);
}
template <typename T0, typename T1, typename T2, typename T3>
Tuple<T0 &, T1 &, T2 &, T3 &>
tie(T0 &a0, T1 &a1, T2 &a2, T3 &a3) {
  return Tuple<T0 &, T1 &, T2 &, T3 &>(a0, a1, a2, a3);
}
template <typename T0, typename T1, typename T2>
Tuple<T0 &, T1 &, T2 &>
tie(T0 &a0, T1 &a1, T2 &a2) {
  return Tuple<T0 &, T1 &, T2 &>(a0, a1, a2);
}
template <typename T0, typename T1>
Tuple<T0 &, T1 &>
tie(T0 &a0, T1 &a1) {
  return Tuple<T0 &, T1 &>(a0, a1);
}
template <typename T0>
Tuple<T0 &>
tie(T0 &a0) {
  return Tuple<T0 &>(a0);
}
inline
Tuple<>
tie() {
  return Tuple<>();
}

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_TUPLE_H
