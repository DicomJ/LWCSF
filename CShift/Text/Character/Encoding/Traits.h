#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_TRAITS_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_TRAITS_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Case/Upper.h"
#include "Text/Character/Code/Case/Lower.h"
#include "Text/Character/Code/Case/Folded.h"
#include "Text/Character/Code/Case/Title.h"


namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {

struct Traits {
  struct Case {
    template <typename Encoding, typename Position> struct Upper
        : Text::Character::Code::Case::Upper<Encoding, Position> {
      Upper(const Encoding &encoding, const Position &begin, const Position &end)
        : Text::Character::Code::Case::Upper<Encoding, Position>(encoding, begin, end) {}
    };
    template <typename Encoding, typename Position> struct Lower
        : Text::Character::Code::Case::Lower<Encoding, Position> {
      Lower(const Encoding &encoding, const Position &begin, const Position &end)
        : Text::Character::Code::Case::Lower<Encoding, Position>(encoding, begin, end) {}
    };
    template <typename Encoding, typename Position> struct Folded
        : Text::Character::Code::Case::Folded<Encoding, Position> {
      Folded(const Encoding &encoding, const Position &begin, const Position &end)
        : Text::Character::Code::Case::Folded<Encoding, Position>(encoding, begin, end) {}
    };
    template <typename Encoding, typename Position> struct Title
        : Text::Character::Code::Case::Title<Encoding, Position> {
      Title(const Encoding &encoding, const Position &begin, const Position &end)
        : Text::Character::Code::Case::Title<Encoding, Position>(encoding, begin, end) {}
    };
  };
};

}}}} // namespace CShift::Text::Character::Encoding

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_TRAITS_H
