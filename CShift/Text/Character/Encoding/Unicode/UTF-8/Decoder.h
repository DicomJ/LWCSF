#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_DECODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_DECODER_H

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
struct Decoder<8, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    Point point() const { return point_; }
    UInt size() const { return size_; }
    Output() : point_(0), size_(0) {}

    template <typename Position>
    Output(Position first, const Position &last) {
      using Text::Character::Code::U;
      typedef LWF::Bits<8> Bits;

      point_ = *first; size_ = 1;
      Bits bits(point_);
      UInt length = bits.countLeadingOne();
      if (0 == length) {
      } else if (1 == length || length > 4) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        point_ = 0;
      } else {
        point_ = bits[Bits::low(8 - (length + 1))];
        for (--length, ++first; length != 0; --length, ++first) {
          if (first == last) {
            LWF::Exception::Throw(Text::IllFormed::Exception());
            point_ = 0; break;
          }
          bits = *first; ++size_;
          if (bits[Bits::High<2>()] != 2) {
            LWF::Exception::Throw(Text::IllFormed::Exception());
            point_ = 0; break;
          }
          point_ <<= 6;
          point_ |= bits[Bits::Low<6>()];
        }
        if (U+0xD800 <= point_ && point_ <= U+0xDFFF) {
          LWF::Exception::Throw(Text::IllFormed::Exception());
          point_ = 0;
        }
      }
    }
    private: Point point_;
    private: Point size_;
  };

  Decoder(const Encoding::Unicode::UTF<8, Char> &/*encoding*/) {}

  template <typename Position>
  Output operator() (const Position &first, const Position &last) const {
    return Output(first, last);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_8_DECODER_H
