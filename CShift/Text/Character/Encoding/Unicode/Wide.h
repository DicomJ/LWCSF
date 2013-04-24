#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_WIDE_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_WIDE_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Encoding/Unicode/UTF-16.h"
#include "Text/Character/Encoding/Unicode/UTF-32.h"


namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

typedef Text::Character::Encoding::Unicode::UTF<LWF::Type<WChar>::sizeInBits, WChar> Wide;

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_WIDE_H
