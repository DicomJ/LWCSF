#ifndef CSHIFT_LWF_LARGE_INTEGER_H
#define CSHIFT_LWF_LARGE_INTEGER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/DWord.h"

namespace CShift {
namespace LWF {
namespace Large {

template <typename Sign, UInt size>
struct Integer {

  private: typedef LWF::DWord<size / 2> DWord; public:
  typedef typename LWF::Integer<size, Sign>::Type Int;
  typedef typename DWord::Word Word;

  operator Int () const { return value; }
  Integer &operator = (Int value) { this->value = value; return *this; }
  Integer(Int value = 0) : value(value) {}

  Integer(Word low, Word high) { dword.low(low); dword.high(high); }
  Word low () const { return dword.low();  }
  Word high() const { return dword.high(); }
  Void low(Word wLow) { dword.low(wLow); }
  Void high(Word wHigh) { dword.high(wHigh); }

  private: union { Int value; typename DWord::template POD<> dword; };
};

#if !PLATFORM_COMPILER_64BITS_INTEGER

template <>
struct Integer<LWF::Kind::Integer::Unsigned, 8> : LWF::DWord<8>::UInt {

  private: typedef LWF::DWord<8>::UInt Unsigned;
           typedef LWF::DWord<8>::Int Signed; public:

  typedef typename Unsigned::Word Word;

  Integer(Word low, Word high) : Unsigned(low, high) {}

  Integer(const Unsigned &u) : Unsigned(u) { }

  Integer &operator = (const Unsigned &u) {
    Unsigned::operator = (u); return *this;
  }

  Integer(Word low = 0) : Unsigned(low) {}

  Integer &operator = (Word low) {
    Unsigned::operator = (low); return *this;
  }

  operator Word () const { return Unsigned::operator Word(); }

  Integer(const Signed &i) : Unsigned(i.low(), i.high()) {}

  Integer &operator = (const Signed &i) {
    this->w.low = i.low(); this->w.high = i.high(); return *this;
  }

  operator Signed () const { return Signed(this->w.low, this->w.high); }
};

template <>
struct Integer<LWF::Kind::Integer::Signed, 8> : LWF::DWord<8>::Int {

  typedef LWF::DWord<8>::Int Base;
  typedef LWF::DWord<8>::UInt Unsigned;

  typedef typename Base::Word Word;
  struct Signed { typedef typename Base::Signed::Word Word; };

  Integer(Word low, Word high) : Base(low, high) {}

  Integer(const Base &i) : Base(i) { }

  Integer &operator = (const Base &i) {
    Base::operator = (i); return *this;
  }

  Integer(Word low = 0) : Base(low) {}

  Integer &operator = (Word low) {
    Base::operator = (low); return *this;
  }

  operator Word () const { return Base::operator Word(); }

  Integer(typename Signed::Word low) : Base(low) {}

  Integer &operator = (typename Signed::Word low) {
    Base::operator = (low); return *this;
  }

  operator typename Signed::Word () const { return Base::operator typename Signed::Word(); }

  Integer(const Unsigned &u) : Base(u.low(), u.high()) {}
  Integer &operator = (const Unsigned &u) {
    Base::operator = (u); return *this;
  }
  operator Unsigned () const { return Unsigned(this->w.low, this->w.high); }
};

#endif // !PLATFORM_COMPILER_64BITS_INTEGER

namespace Signed {
  typedef LWF::Large::Integer<LWF::Kind::Integer::Signed, 8> Integer;
}
namespace Unsigned {
  typedef LWF::Large::Integer<LWF::Kind::Integer::Unsigned, 8> Integer;
}

typedef LWF::Large::Signed::Integer Int;
typedef LWF::Large::Unsigned::Integer UInt;

}}} // namespace CShift::LWF::Large

#endif // CSHIFT_LWF_LARGE_INTEGER_H
