#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_DECODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_DECODER_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Point.h"
#include "Text/Character/Encoding/Unicode/UTF.h"
#include "Text/Character/Encoding/Unicode/Decoder.h"
#include "Text/IllFormed/Exception.h"
#include "LWF/Bits.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

template <typename Char>
struct Decoder<16, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    Point point() const { return point_; }
    UInt size() const { return size_; }
    Output() : point_(0), size_(0) {}
    template <typename Position>
    Output(Position first, const Position &last) {
      using Text::Character::Code::U;
      typedef LWF::Bits<16> Bits;

      point_ = typename Bits::Type(*first); size_ = 1;

      if (U+0xD800 <= point_ && point_ <= U+0xDFFF) {
        typename Bits::Type trail;
        if (!(U+0xD800 <= point_ && point_ <= U+0xDBFF) ||
            (++first == last) ||
            ((trail = *first), !(U+0xDC00 <= trail && trail <= U+0xDFFF))) {
          LWF::Exception::Throw(Text::IllFormed::Exception());
          point_ = 0;
        } else {
          size_ = 2;
          const UInt low = 10;
          typedef LWF::Bits<16> Bits;
          point_ =  (U+0x10000) +
                    ((Bits(point_)[typename Bits::template Low <low >()] << low) |
                      Bits(trail )[typename Bits::template Low <low >()]);
        }
      }
    }
    private: Point point_;
    private: UInt size_;
  };

  Decoder(const Encoding::Unicode::UTF<16, Char> &/*encoding*/) {}

  template <typename Position>
  Output operator() (const Position &first, const Position &last) const {
    return Output(first, last);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_16_DECODER_H
