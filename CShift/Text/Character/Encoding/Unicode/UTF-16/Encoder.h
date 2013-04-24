#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_ENCODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_ENCODER_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Point.h"
#include "Text/Character/Encoding/Unicode/UTF.h"
#include "Text/Character/Encoding/Unicode/Encoder.h"
#include "Text/IllFormed/Exception.h"
#include "LWF/Bits.h"
#include "LWF/Range.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

template <typename Char>
struct Encoder<16, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    typedef LWF::Range<LWF::Weak::Ptr<const Char[]> > Print;

    Print print() const { return Print(unit + 0, unit + type); }

    Output(Point point = 0) {
      using Text::Character::Code::U;

      if (point > U+0x10FFFF || (U+0xD800 <= point && point <= U+0xDFFF)) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        type = IllFormed;
      } else {
        if (point > U+0xFFFF) {
          const UInt size = LWF::Type<Point>::sizeInBits,
                     low = 10, high = size - low;
          typedef LWF::Bits<size> Bits;
          Bits bits(point - (U+0x10000));
          unit[0]  = Char((U+0xD800) | bits[Bits::High<high>()]);
          unit[1] = Char((U+0xDC00) | bits[Bits::Low<low>()]);
          type = Surrogate;
        } else {
          unit[0] = Char(point); type = BMP;
        }
      }
    }

    private: Char unit[2];
    private: enum { IllFormed = 0, BMP = 1, Surrogate = 2 } type;
  };

  Encoder(const Encoding::Unicode::UTF<16, Char> &/*encoding*/) {}

  Output operator()(const Text::Character::Code::Point &point) {
    return Output(point);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_ENCODER_H
