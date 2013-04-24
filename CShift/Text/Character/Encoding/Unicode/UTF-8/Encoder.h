#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_ENCODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_ENCODER_H

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
struct Encoder<8, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    typedef LWF::Range<LWF::Weak::Ptr<const Char[]> > Print;

    Print print() const { return Print(unit + 0, unit + length); }

    Output(const Point &point = 0) {
      using Text::Character::Code::U;
      const UInt size = LWF::Type<Point>::sizeInBits;
      typedef LWF::Bits<size> Bits;
      typedef LWF::Bit::Mask<size> Mask;

      Bits bits(point);
      if        (point <= Mask::Low       <7>::bits) {
        length = 1;
        unit[0] = Char(point);
      } else if (point <= Mask::Low<5 + 6>::bits) {
        length = 2;
        unit[0] = (U+0xC0) | bits[Bits::Middle< 6, 5>()];
        unit[1] = (U+0x80) | bits[Bits::Low   <    6>()];
      } else if (U+0xD800 <= point && point <= U+0xDFFF) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        length = 0;
      } else if (point <= Mask::Low<4 + 6 + 6>::bits) {
        length = 3;
        unit[0] = (U+0xE0) | bits[Bits::Middle<12, 4>()];
        unit[1] = (U+0x80) | bits[Bits::Middle< 6, 6>()];
        unit[2] = (U+0x80) | bits[Bits::Low   <    6>()];
      } else if (point <= U+0x10FFFF) {
        length = 4;
        unit[0] = (U+0xF0) | bits[Bits::Middle<18, 3>()];
        unit[1] = (U+0x80) | bits[Bits::Middle<12, 6>()];
        unit[2] = (U+0x80) | bits[Bits::Middle< 6, 6>()];
        unit[3] = (U+0x80) | bits[Bits::Low   <    6>()];
      } else {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        length = 0;
      }
    }

    private: Char unit[4];
    private: UInt length;
  };

  Encoder(const Encoding::Unicode::UTF<8, Char> &/*encoding*/) {}

  Output operator()(const Text::Character::Code::Point &point) {
    return Output(point);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_ENCODER_H
