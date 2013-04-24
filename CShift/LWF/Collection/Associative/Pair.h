#ifndef CSHIFT_LWF_COLLECTION_ASSOCIATIVE_PAIR_H
#define CSHIFT_LWF_COLLECTION_ASSOCIATIVE_PAIR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Pair.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Associative {

template <typename K, typename T>
struct Pair : LWF::Pair<K, T> { private: typedef LWF::Pair<K, T> Base; public:

  typedef typename Base::First::Type Key;
  typedef typename Base::Second::Type Type;

  operator const Key & () const { return Base::first(); }
  operator Key & () { return Base::first(); }

  const Key &key() const { return Base::first(); }
  Key &key() { return Base::first(); }

  const Type &value() const { return Base::second(); }
  Type &value() { return Base::second(); }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Pair(typename Base::First::Rvalue::Reference first,
       typename Base::Second::Rvalue::Reference second = Type())
    : Base(first, second) {}
  #else // !C++11
  Pair(typename Base::First::Reference first,
       typename Base::Second::Reference second = Type())
    : Base(first, second){}
  #endif // !C++11

  #if PLATFORM_COMPILER_RVALUE_REFERENCE

  Pair(Pair &&pair) : Base(LWF::Forward::reference<Base>(pair)) {}
  Pair(Base &&base) : Base(LWF::Forward::reference<Base>(base)) {}

  template <typename U0, typename U1>
  Pair(Pair<U0, U1> &&pair)
    : Base(LWF::Forward::reference<Pair<U0, U1> >(pair)) {}
  template <typename U0, typename U1>
  Pair(LWF::Pair<U0, U1> &&base)
    : Base(LWF::Forward::reference<LWF::Pair<U0, U1> >(base)) {}

  #endif // C++11

  Pair(const Pair &pair) : Base(pair) {}
  Pair(const Base &base) : Base(base) {}

  template <typename U0, typename U1>
  Pair(const Pair<U0, U1> &pair) : Base(pair) {}
  template <typename U0, typename U1>
  Pair(const LWF::Pair<U0, U1> &base) : Base(base) {}
};

}}}} // namespace CShift::LWF::Collection::Associative

#endif // CSHIFT_LWF_COLLECTION_ASSOCIATIVE_PAIR_H
