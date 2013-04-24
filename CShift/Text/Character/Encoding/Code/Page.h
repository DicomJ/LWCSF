#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_CODE_PAGE_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_CODE_PAGE_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Encoding/Traits.h"


namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Code {

struct Page : Text::Character::Encoding::Traits { struct Nonconst;

  typedef typename LWF::Select::Char<8>::Type Char;
  struct Encoder;
  struct Decoder;

  Bool operator == (const Page &) const { return True; }
  Bool operator != (const Page &page) const { return !(*this == page); }

  explicit Page(const Char * = 0) {}
};

struct Page::Encoder {
  struct Output {
    typedef Text::Character::Code::Point Point;
    typedef LWF::Range<LWF::Weak::Ptr<const Char8[]> > Print;

    Print print() const { return Print(unit + 0, unit + length); }

    Output(const Point &/*point*/ = 0) {
      // TODO: put values to units
      length = 0;
    }

    private: Char8 unit[2];
    private: UInt length;
  };

  Encoder(const Code::Page &/*encoding*/) {}

  Output operator()(const Text::Character::Code::Point &point) {
    return Output(point);
  }
};

struct Page::Decoder {

  struct Output {
    typedef Text::Character::Code::Point Point;
    Point point() const { return point_; }
    UInt size() const { return size_; }
    Output() : point_(0), size_(0) {}
    template <typename Position>
    Output(const Position &/*first*/, const Position &/*last*/) {
       point_ = 0; // TODO
       size_ = 1;
    }
    private: Point point_;
    private: Point size_;
  };

  Decoder(const Code::Page &/*encoding*/) {}

  template <typename Position>
  Output operator() (const Position &first, const Position &last) const {
    return Output(first, last);
  }
};

}}}}} // namespace CShift::Text::Character::Encoding::Code

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_CODE_PAGE_H
