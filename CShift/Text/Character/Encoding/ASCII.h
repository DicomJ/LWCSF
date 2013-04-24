#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_ASCII_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_ASCII_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Encoding/Traits.h"
#include "Text/IllFormed/Exception.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {

struct ASCII : Text::Character::Encoding::Traits { struct Nonconst;

  typedef typename LWF::Select::Char<8>::Type Char;
  struct Encoder;
  struct Decoder;

  Bool operator == (const ASCII &) const { return True; }
  Bool operator != (const ASCII &) const { return False; }
};

struct ASCII::Encoder {
  struct Output {
    typedef Text::Character::Code::Point Point;
    typedef ASCII::Char Print;

    Print print() const { return print_; }

    Output(Point point = 0) {
      using Text::Character::Code::U;
      if (point > U+0x7F) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        point = 0;
      }
      print_ = Print(point);
    }
    private: Print print_;
  };

  Encoder(const ASCII &/*encoding*/) {}

  Output operator()(const Text::Character::Code::Point &point) {
    return Output(point);
  }
};

struct ASCII::Decoder {

  struct Output {
    typedef Text::Character::Code::Point Point;
    Point point() const { return point_; }
    UInt size() const { return size_; }
    Output() : point_(0), size_(0) {}
    template <typename Position>
    Output(const Position &first, const Position &/*last*/) {
      using Text::Character::Code::U;
      point_= Point(*first);
      if (point_ > U+0x7F) {
        LWF::Exception::Throw(Text::IllFormed::Exception());
        point_ = 0;
      }
      size_ = 1;
    }
    private: Point point_;
    private: Point size_;
  };

  Decoder(const ASCII &/*encoding*/) {}

  template <typename Position>
  Output operator() (const Position &first, const Position &last) const {
    return Output(first, last);
  }
};

}}}} // namespace CShift::Text::Character::Encoding

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_ASCII_H
