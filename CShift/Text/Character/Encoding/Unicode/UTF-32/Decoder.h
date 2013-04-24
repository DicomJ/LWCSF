#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_DECODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_DECODER_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Point.h"
#include "Text/Character/Encoding/Unicode/UTF.h"
#include "Text/Character/Encoding/Unicode/Decoder.h"
#include "Text/IllFormed/Exception.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

template <typename Char>
struct Decoder<32, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    Point point() const { return point_; }
    UInt size() const { return size_; }
    Output() : point_(0), size_(0) {}
    template <typename Position>
    Output(const Position &first, const Position &/*last*/) {
      using Text::Character::Code::U;
      point_= Point(*first);
      if (point_ > U+0x10FFFF || (U+0xD800 <= point_ && point_ <= U+0xDFFF)) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        point_ = 0;
      }
      size_ = 1;
    }
    private: Point point_;
    private: Point size_;
  };

  Decoder(const Encoding::Unicode::UTF<32, Char> &/*encoding*/) {}

  template <typename Position>
  Output operator() (const Position &first, const Position &last) const {
    return Output(first, last);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_DECODER_H
