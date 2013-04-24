#ifndef CSHIFT_LWF_DWORD_H
#define CSHIFT_LWF_DWORD_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Integer.h"
#include "LWF/Endian.h"

namespace CShift {
namespace LWF {

template <UInt size>
struct DWord {

  typedef typename LWF::Integer<size / 2, LWF::Kind::Integer::Unsigned>::Type Word;

  template <Endian::Type endian = LWF::endian, typename U = Void>
  struct POD;

  template <typename Sign, typename U = Void>
  struct Integer;

  typedef Integer<LWF::Kind::Integer::Unsigned> UInt;
  typedef Integer<LWF::Kind::Integer::Signed> Int;

}; // DWord

template <UInt size>
template <typename U>
struct DWord<size>::POD<Endian::Little, U> {
  typedef DWord<size>::Word Word;

  Word low() const { return w.low; }
  Word high() const { return w.high; }

  Void low(Word wLow) { w.low = wLow; }
  Void high(Word wHigh) { w.high = wHigh; }

  protected: struct { Word low, high; } w;
};

template <UInt size>
template <typename U>
struct DWord<size>::POD<Endian::Big, U> {
  typedef DWord<size>::Word Word;

  protected: struct { Word high, low; } w;
};

template <UInt size>
template <typename U>
struct DWord<size>::Integer<LWF::Kind::Integer::Unsigned, U> : DWord<size>::template POD<> {

  typedef  DWord<size>::Word Word;

  private: typedef typename DWord<size>::template POD<> Base;
           typedef DWord<size>::Integer<LWF::Kind::Integer::Signed> Signed;
           typedef typename LWF::Integer<LWF::Type<Word>::size>::Type SWord; public:

  Integer(Word low, Word high) {
    this->w.low = low; this->w.high = high;
  }

  Integer(const Integer &u) {
    this->w.low = u.w.low; this->w.high = u.w.high;
  }

  Integer(const Signed &i) {
    this->w.low = i.low(); this->w.high = i.high();
  }

  Integer(const Word low = 0) {
    this->w.low = low; this->w.high = 0;
  }

  Integer(SWord low) {
    *this = Signed(low);
  }

  Integer &operator = (const Integer &u) {
    this->w.low = u.w.low; this->w.high = u.w.high; return *this;
  }

  Integer &operator = (const Signed &i) {
    return *this = Integer(i);
  }

  Integer &operator = (Word low) {
    return *this = Integer(low);
  }

  Integer &operator = (SWord low) {
    return *this = Integer(low);
  }

  operator Signed () const { return Signed(this->w.low, this->w.high); }

  operator Word () const { return this->w.low; }

  Bool operator == (const Integer &u) const {
    return this->w.low == u.w.low && this->w.high == u.w.high;
  }

  Bool operator == (const Signed &i) const {
    return *this == Integer(i);
  }

  Bool operator == (Word low) const {
    return *this == Integer(low);
  }

  Bool operator == (SWord low) const {
    return *this == Integer(low);
  }

  Bool operator != (const Integer &u) const {
    return !(*this == u);
  }

  Bool operator != (const Signed &i) const {
    return *this != Integer(i);
  }

  Bool operator != (Word low) const {
    return *this != Integer(low);
  }

  Bool operator != (SWord low) const {
    return *this == Integer(low);
  }

  Bool operator > (const Integer &u) const {
    return this->w.high != u.w.high ? this->w.high > u.w.high : this->w.low > u.w.low;
  }

  Bool operator > (const Signed &i) const {
    return *this > Integer(i);
  }

  Bool operator > (Word low) const {
    return *this > Integer(low);
  }

  Bool operator > (SWord low) const {
    return *this > Integer(low);
  }

  Bool operator >= (const Integer &u) const {
    return this->w.high != u.w.high ? this->w.high >= u.w.high : this->w.low >= u.w.low;
  }

  Bool operator >= (const Signed &i) const {
    return *this >= Integer(i);
  }

  Bool operator >= (Word low) const {
    return *this >= Integer(low);
  }

  Bool operator >= (SWord low) const {
    return *this >= Integer(low);
  }

  Bool operator < (const Integer &u) const {
    return this->w.high != u.w.high ? this->w.high < u.w.high : this->w.low < u.w.low;
  }

  Bool operator < (const Signed &i) const {
    return *this < Integer(i);
  }

  Bool operator < (Word low) const {
    return *this < Integer(low);
  }

  Bool operator < (SWord low) const {
    return *this < Integer(low);
  }

  Bool operator <= (const Integer &u) const {
    return this->w.high != u.w.high ? this->w.high <= u.w.high : this->w.low <= u.w.low;
  }

  Bool operator <= (const Signed &i) const {
    return *this <= Integer(i);
  }

  Bool operator <= (Word low) const {
    return *this <= Integer(low);
  }

  Bool operator <= (SWord low) const {
    return *this <= Integer(low);
  }

  Integer operator ~ () const {
    return Integer(~this->w.low, ~this->w.high);
  }

  Integer operator ^ (const Integer &u) const {
    return Integer(this->w.low ^ u.w.low, this->w.high ^ u.w.high);
  }

  Integer operator ^ (const Signed &i) const {
    return *this ^ Integer(i);
  }

  Integer operator ^ (Word low) const {
    return *this ^ Integer(low);
  }

  Integer operator ^ (SWord low) const {
    return *this ^ Integer(low);
  }

  Integer operator | (const Integer &u) const {
    return Integer(this->w.low | u.w.low, this->w.high | u.w.high);
  }

  Integer operator | (const Signed &i) const {
    return *this | Integer(i);
  }

  Integer operator | (Word low) const {
    return *this | Integer(low);
  }

  Integer operator | (SWord low) const {
    return *this | Integer(low);
  }

  Integer operator & (const Integer &u) const {
    return Integer(this->w.low & u.w.low, this->w.high & u.w.high);
  }

  Integer operator & (const Signed &i) const {
    return *this & Integer(i);
  }

  Integer operator & (Word low) const {
    return *this & Integer(low);
  }

  Integer operator & (SWord low) const {
    return *this & Integer(low);
  }

  Integer operator >> (UInt n) const {
    return Integer((this->w.low >> n) | (this->w.high << (LWF::Type<Word>::suzeInButs - n)),
                    this->w.high >> n);
  }

  Integer operator << (UInt n) const {

    return Integer(this->w.low << n,
                   (this->w.high << n) | (this->w.low >> (LWF::Type<Word>::suzeInButs - n)));
  }

  Integer operator + (const Integer &u) const {
    Word low = this->w.low + u.w.low;
    return Integer(low, this->w.high + u.w.high + (this->w.low < low ? 1 : 0));
  }

  Integer operator + (const Signed &i) const {
    return *this + Integer(i);
  }

  Integer operator + (Word low) const {
    return *this + Integer(low);
  }

  Integer operator + (SWord low) const {
    return *this + Integer(low);
  }

  Integer operator - (const Integer &u) const {
    return *this + -u;
  }

  Integer operator - (const Signed &i) const {
    return *this - Integer(i);
  }

  Integer operator - (Word low) const {
    return *this - Integer(low);
  }

  Integer operator - (SWord low) const {
    return *this - Integer(low);
  }

  Integer operator - () const {
    return (~*this) + 1;
  }

  Integer &operator ++ () {
    *this += 1;
  }

  Integer &operator -- () {
    *this -= 1;
  }

  Integer operator ++ (int) {
    Integer i = *this;  ++*this; return i;
  }

  Integer operator -- (int) {
    Integer i = *this;  --*this; return i;
  }

  Integer &operator += (const Integer &u) {
    return *this = *this + u;
  }

  Integer operator += (const Signed &i) const {
    return *this += Integer(i);
  }

  Integer operator += (Word low) const {
    return *this += Integer(low);
  }

  Integer operator += (SWord low) const {
    return *this += Integer(low);
  }

  Integer &operator -= (const Integer &u) {
    return *this += -u;
  }

  Integer operator -= (const Signed &i) const {
    return *this -= Integer(i);
  }

  Integer operator -= (Word low) const {
    return *this -= Integer(low);
  }

  Integer operator -= (SWord low) const {
    return *this -= Integer(low);
  }

  Integer &operator >>= (UInt n) {
    return *this = *this >> n;
  }

  Integer &operator <<= (UInt n) {
    return *this = *this << n;
  }


  Integer &operator |= (const Integer &u) {
    return *this = *this | u;
  }

  Integer operator |= (const Signed &i) const {
    return *this |= Integer(i);
  }

  Integer operator |= (Word low) const {
    return *this |= Integer(low);
  }

  Integer operator |= (SWord low) const {
    return *this |= Integer(low);
  }

  Integer &operator &= (const Integer &u) {
    return *this = *this & u;
  }

  Integer operator &= (const Signed &i) const {
    return *this &= Integer(i);
  }

  Integer operator &= (Word low) const {
    return *this &= Integer(low);
  }

  Integer operator &= (SWord low) const {
    return *this &= Integer(low);
  }

  Integer &operator ^= (const Integer &u) {
    return *this = *this ^ u;
  }

  Integer operator ^= (const Signed &i) const {
    return *this ^= Integer(i);
  }

  Integer operator ^= (Word low) const {
    return *this ^= Integer(low);
  }

  Integer operator ^= (SWord low) const {
    return *this ^= Integer(low);
  }
};

template <UInt size>
template <typename U>
struct DWord<size>::Integer<LWF::Kind::Integer::Signed, U>
    : Integer<LWF::Kind::Integer::Unsigned> {
  private: typedef Integer<LWF::Kind::Integer::Unsigned> Unsigned; public:
  typedef DWord<size>::Word Word;
  struct Signed { typedef typename LWF::Integer<LWF::Type<typename Unsigned::Word>::size>::Type Word; };


  Integer(Word low, Word high) : Unsigned(low, high) {}

  Integer(const Integer &i) : Unsigned(i) { }

  Integer &operator = (const Integer &i) {
    Unsigned::operator = (i); return *this;
  }

  Integer(Word low = 0) : Unsigned(low) {}

  Integer &operator = (Word low) {
    Unsigned::operator = (low); return *this;
  }

  operator Word () const { return Unsigned::operator Word(); }

  Integer(typename Signed::Word low) : Unsigned(low, low < 0 ? -1 : 0) {}

  Integer &operator = (typename Signed::Word low) {
    this->w.low = low; this->w.high = low < 0 ? -1 : 0; return *this;
  }

  operator typename Signed::Word () const { return this->w.low; }

  Integer(const Unsigned &u) : Unsigned(u.low(), u.high()) {}

  Integer &operator = (const Unsigned &u) {
    this->w.low = u.low(); this->w.high = u.high(); return *this;
  }
  operator Unsigned () const { return Unsigned(this->w.low, this->w.high); }
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_DWORD_H
