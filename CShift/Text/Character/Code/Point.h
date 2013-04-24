#ifndef CSHIFT_TEXT_CHARACTER_CODE_POINT_H
#define CSHIFT_TEXT_CHARACTER_CODE_POINT_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace Text {
namespace Character {
namespace Code {

typedef UInt Point;

struct { Point operator + (Point point) const { return point; } } const U = U;

}}}} // namespace CShift::Text::Character::Code

#endif // CSHIFT_TEXT_CHARACTER_CODE_POINT_H
