#ifndef CSHIFT_TEXT_CHARACTER_CODE_CASE_LOWER_H
#define CSHIFT_TEXT_CHARACTER_CODE_CASE_LOWER_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Code/Point.h"


namespace CShift {
namespace Text {
namespace Character {
namespace Code {
namespace Case {

template <typename Encoding, typename Position>
struct Lower {
  Lower(const Encoding &, const Position &/*begin*/, const Position &/*end*/) {}

  Code::Point operator() (const Code::Point &point, const Position &/*position*/) const {
    return point; // TODO
  }
};

}}}}} // namespace CShift::Text::Character::Code::Case

#endif // CSHIFT_TEXT_CHARACTER_CODE_CASE_LOWER_H
