#ifndef CSHIFT_LWF_BIT_MASK
#define CSHIFT_LWF_BIT_MASK

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Integer.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/OutOfRange/Exception.h"

namespace CShift {
namespace LWF {
namespace Bit {

namespace Traits {

template <UInt bytes>
struct Mask {

  typedef typename LWF::Unsigned::Integer<bytes>::Type Type;
  static const UInt bits = 8 * bytes;

  template <UInt N, Bool = (Mask::bits >= N), typename U = Void> struct Low;
  template <typename U>
  struct Low</*Mask::bits*/8 * bytes, True, U> {
    static const Type bits = LWF::Type<Type>::max;
  };
  template <UInt N, typename U>
  struct Low<N, True, U> {
    static const Type bits = (Type(1) << N) - 1;
  };
  static Type low(UInt N) {
    if (N > Mask::bits) {
      LWF::Exception::Throw(LWF::OutOfRange::Exception());
      return 0;
    } return (Mask::bits == N) ? Low<Mask::bits>::bits : (Type(1) << N) - 1;
  }

  template <UInt N, Bool = (Mask::bits >= N), typename U = Void> struct High;
  template <typename U>
  struct High</*Mask::bits*/8 * bytes, True, U> {
    static const Type bits = LWF::Type<Type>::max;
  };
  template <UInt N, typename U>
  struct High<N, True, U> {
    static const Type bits = Type(~Low<Mask::bits - N>::bits);
  };
  static Type high(UInt N) {
    if (N > Mask::bits) {
      LWF::Exception::Throw(LWF::OutOfRange::Exception());
      return 0;
    } return (Mask::bits == N) ? High<Mask::bits>::bits : ~low(Mask::bits - N);
  }

  template <UInt N, UInt count, Bool = (Mask::bits >= N + count)> struct Middle;

  template <UInt N, UInt count>
  struct Middle<N, count, True> {
    static const Type bits = Type(~(Low<N>::bits |
                                    Type(High<Mask::bits - (N + count)>::bits)));
  };
  static Type middle(UInt N, UInt count) {
    if (N + count > Mask::bits) {
      LWF::Exception::Throw(LWF::OutOfRange::Exception());
      return 0;
    } return ~(low(N) | high(Mask::bits - (N + count)));
  }
};

} // namespace Traits

template <UInt bits, Bool = (bits % 8 == 0)>
struct Mask;
template <UInt bits>
struct Mask<bits, True> : LWF::Bit::Traits::Mask<bits/8> {};


typedef Mask<8 > Mask8;
typedef Mask<16> Mask16;
typedef Mask<32> Mask32;
#if PLATFORM_COMPILER_64BITS_INTEGER
typedef Mask<64> Mask64;
#endif // C++99

}}} // namespace CShift::LWF::Bit

#endif // CSHIFT_LWF_BIT_MASK
