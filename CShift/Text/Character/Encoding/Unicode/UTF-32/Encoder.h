#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_ENCODER_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_ENCODER_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Point.h"
#include "Text/Character/Encoding/Unicode/UTF.h"
#include "Text/Character/Encoding/Unicode/Encoder.h"
#include "Text/IllFormed/Exception.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

template <typename Char>
struct Encoder<32, Char> {

  struct Output {
    typedef Text::Character::Code::Point Point;
    typedef Char Print;

    Print print() const { return print_; }

    Output(Point point = 0) {
      using Text::Character::Code::U;
      if (point > U+0x10FFFF || (U+0xD800 <= point && point <= U+0xDFFF)) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        point = 0;
      }
      print_ = Print(point);
    }
    private: Print print_;
  };

  Encoder(const Encoding::Unicode::UTF<32, Char> &/*encoding*/) {}

  Output operator()(const Text::Character::Code::Point &point) {
    return Output(point);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_32_ENCODER_H
