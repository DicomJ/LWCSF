#ifndef CSHIFT_LWF_BITS
#define CSHIFT_LWF_BITS

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Bit/Mask.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/OutOfRange/Exception.h"

namespace CShift {
namespace LWF {

namespace Traits {

template <UInt bytes>
struct Bits {

  typedef typename LWF::Unsigned::Integer<bytes>::Type Type;
  static const UInt count = 8 * bytes;
  static const UInt power = Bits::template Power<>::size;

  template <UInt N,              Bool = (N > Bits::count)           >
  struct Low;
  template <UInt N,              Bool = (N > Bits::count)           >
  struct High;
  template <UInt N, UInt count_, Bool = ((N + count_) > Bits::count)>
  struct Middle;

  template <UInt N             > struct Low   <N        , False> {};
  template <UInt N             > struct High  <N        , False> {};
  template <UInt N, UInt count_> struct Middle<N, count_, False> {};

  struct Dynamic;
  static typename Dynamic::Low    low   (UInt N) { return N; }
  static typename Dynamic::High   high  (UInt N) { return N; }
  static typename Dynamic::Middle middle(UInt N, UInt count) {
    return typename Dynamic::Middle(N, count);
  }

  UInt countLeadingZero() const {
    Type bits = Bits::template Round<>::one(this->bits);
    return bits != Type(-1) ? Bits::Debruijn::most[
                              Bits::Debruijn::index(bits + 1)] : 0;
  }
  UInt countTrailingZero() const {
    return bits != 0 ? Bits::Debruijn::least[
                       Bits::Debruijn::index(bits & (-bits))]: 8 * bytes;
  }
  UInt countLeadingOne() const { return Bits(~bits).countLeadingZero(); }
  UInt countTrailingOne() const { return Bits(~bits).countTrailingZero(); }

  private: struct Basic;
  public: template <typename Part,
                    typename Base = typename Basic::template Sub<Part> >
  struct Sub;

  template <typename Part>
  Sub<Part> operator [] (const Part &part) { return Sub<Part>(*this, part); }

  template <typename Part>
  Type operator [] (const Part &part) const {
    return const_cast<Bits &>(*this)[part];
  }

  template <typename Part>
  Type operator & (const Part &part) const {
    return ~const_cast<Bits &>(*this)[part];
  }

  Bits(const Type &bits_) : bits(bits_) {}
  Bits &operator = (const Type &bits) { this->bits = bits; return *this; }
  operator Type () const { return bits; }

  // Specialization

  template <typename Base, UInt N>
  struct Sub<Low<N>, Base> : Base {
    Sub(Bits &bits, const Low<N> &) : Base(bits) {}
    operator Type() const { return ~(*this); }
    Type operator ~ () const {
      return Type(Base::bits) &
             LWF::Bit::Mask<Bits::count>::template Low<N>::bits;
    }
    Bits &operator = (const Type &bits) {
      return Base::bits = (Bits(bits) & Low<N>()) |
                          (Base::bits & High<Bits::count - N>());
    }
  };

  template <typename Base, UInt N>
  struct Sub<High<N>, Base> : Base {
    Sub(Bits &bits, const High<N> &) : Base(bits) {}
    operator Type() const { return Type(Base::bits) >> (Bits::count - N); }
    Type operator ~ () const {
      return Type(Base::bits) &
             LWF::Bit::Mask<Bits::count>::template High<N>::bits;
    }
    Bits &operator = (const Type &bits) {
      return Base::bits = (Base::bits & Low<Bits::count - N>()) |
                          (bits << (Bits::count - N));
    }
  };

  template <typename Base, UInt N, UInt count_>
  struct Sub<Middle<N, count_>, Base> : Base {
    Sub(Bits &bits, const Middle<N, count_> &) : Base(bits) {}
    operator Type() const {
        return Bits(Base::bits[High<Bits::count - N>()])[Low<count_>()];
    }
    Type operator ~ () const {
      return Type(Base::bits) &
             LWF::Bit::Mask<Bits::count>::template Middle<N, count_>::bits;
    }
    Bits &operator = (const Type &bits) {
      return Base::bits = (Base::bits & Low<N>()) |
                          ((Bits(bits)& Low<count_>()) << N) |
                          (Base::bits & High<Bits::count - (N + count_)>());
    }
  };

  template <typename Base>
  struct Sub<typename Dynamic::Low, Base> : Base {
    Sub(Bits &bits, const typename Dynamic::Low &part) : Base(bits, part) {}
    operator Type() const { return ~(*this); }
    Type operator ~ () const {
      return Type(Base::bits) &
             LWF::Bit::Mask<Bits::count>::low(Dynamic::Low::N);
    }
    Bits &operator = (const Type &bits) {
      return Base::bits = (Bits(bits) & low(Dynamic::Low::N)) |
                          (Base::bits & high(Bits::count - Dynamic::Low::N));
    }
  };

  template <typename Base>
  struct Sub<typename Dynamic::High, Base> : Base {
    Sub(Bits &bits, const typename Dynamic::High &part) : Base(bits, part) {}
    operator Type() const {
      return Type(Base::bits) >> (Bits::count - Dynamic::High::N);
    }
    Type operator ~ () const {
      return Type(Base::bits) &
             LWF::Bit::Mask<Bits::count>::high(Dynamic::High::N);
    }

    Bits &operator = (const Type &bits) {
      return Base::bits = (Base::bits & low(Bits::count - Dynamic::High::N)) |
                          (bits << (Bits::count - Dynamic::High::N));
    }
  };

  template <typename Base>
  struct Sub<typename Dynamic::Middle, Base> : Base {
    Sub(Bits &bits, const typename Dynamic::Middle &part) : Base(bits, part) {}
    operator Type() const {
      return Bits(Base::bits[high(Bits::count - Dynamic::Middle::N)])
                            [low(Dynamic::Middle::count)];
    }
    Type operator ~ () const {
      return Type(Base::bits) & LWF::Bit::Mask<Bits::count>::
              middle(Dynamic::Middle::N, Dynamic::Middle::count);
    }
    Bits &operator = (const Type &bits) {
      return Base::bits =
        (Base::bits & low(Dynamic::Middle::N)) |
        ((Bits(bits) & low(Dynamic::Middle::count)) << Dynamic::Middle::N) |
        (Base::bits & high(Bits::count - (Dynamic::Middle::N + Dynamic::Middle::count)));
    }
  };

  struct Dynamic {
    struct Low {  UInt N;
      Low(UInt N_) : N(N_) {
        if (N > Bits::count) {
          LWF::Exception::Throw(LWF::OutOfRange::Exception());
          N = 0;
        }
      }
    };
    struct High { UInt N;
      High(UInt N_) : N(N_) {
        if (N > Bits::count) {
          LWF::Exception::Throw(LWF::OutOfRange::Exception());
          N = 0;
        }
      }
    };
    struct Middle { UInt N, count;
      Middle(UInt N_, UInt count_) : N(N_), count(count_) {
        if (N + count > Bits::count) {
          LWF::Exception::Throw(LWF::OutOfRange::Exception());
          N = count = 0;
        }
      }
    };
  };

  private: struct Basic {
    template <typename Part>
    struct Sub : protected Part {
      Sub(Bits &bits_) : bits(bits_) {}
      Sub(Bits &bits_, const Part &part) : Part(part), bits(bits_) {}
      protected: Bits &bits;
    };
  };

  private: template <UInt N = Bits::count, typename U = Void>
  struct Round;

  template <typename U>
  struct Round< 8, U> { static Type one(Type bits) {
    bits |= bits >> 1;
    bits |= bits >> 2;
    return bits | (bits >> 4);
  }};
  template <typename U>
  struct Round<16, U> { static Type one(Type bits) {
    bits = Round<8>::one(bits);
    return bits | (bits >> 8);
  }};
  template <typename U>
  struct Round<32, U> { static Type one(Type bits) {
    bits = Round<16>::one(bits);
    return bits | (bits >> 16);
  }};
  #if PLATFORM_COMPILER_64BITS_INTEGER
  template <typename U>
  struct Round<64, U> { static Type one(Type bits) {
    bits = Round<32>::one(bits);
    return bits | (bits >> 32);
  }};
  #endif //PLATFORM_COMPILER_64BITS_INTEGER

  private: template <UInt N = Bits::count, typename U = Void>
  struct Power;

  template <typename U>
  struct Power< 8, U> { static const UInt size = 3; };
  template <typename U>
  struct Power<16, U> { static const UInt size = 4; };
  template <typename U>
  struct Power<32, U> { static const UInt size = 5; };
  #if PLATFORM_COMPILER_64BITS_INTEGER
  template <typename U>
  struct Power<64, U> { static const UInt size = 6; };
  #endif //PLATFORM_COMPILER_64BITS_INTEGER

  private: struct Debruijn {

    static UInt index(const Type &one) {
      return Type(Debruijn::Constant<>::value * one) >>
             (Bits::count - Bits::power);
    }

    static const UInt least[];
    static const UInt most[];

    private: template <UInt N = Bits::count, typename U = Void>
    struct Constant;

    template <typename U>
    struct Constant< 8, U> { static const Type value = 0x17; };
    template <typename U>
    struct Constant<16, U> { static const Type value = 0x09AF; };
    template <typename U>
    struct Constant<32, U> { static const Type value = 0x04653ADF; };
    #if PLATFORM_COMPILER_64BITS_INTEGER
    template <typename U>
    struct Constant<64, U> { static const Type value = 0x0218A392CD3D5DBF; };
    #endif //PLATFORM_COMPILER_64BITS_INTEGER
  };

  private: Type bits;
};

} // namespace Traits

template <UInt bits, Bool = (bits % 8 == 0)>
struct Bits;
template <UInt bits>
struct Bits<bits, True> : LWF::Traits::Bits<bits/8> {
  typedef LWF::Traits::Bits<bits / 8> Base;
  typedef typename Base::Type Type;
  Bits(const Type &bits_) : Base(bits_) {}
};

typedef Bits<8 > Bits8 ;
typedef Bits<16> Bits16;
typedef Bits<32> Bits32;
#if PLATFORM_COMPILER_64BITS_INTEGER
typedef Bits<64> Bits64;
#endif // C++99

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_BITS
