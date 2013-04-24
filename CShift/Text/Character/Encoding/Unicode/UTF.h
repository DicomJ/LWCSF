#ifndef CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_H
#define CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Character/Encoding/Traits.h"
#include "Text/Character/Encoding/Unicode/Encoder.h"
#include "Text/Character/Encoding/Unicode/Decoder.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace Text {
namespace Character {
namespace Encoding {
namespace Unicode {

template <UInt bits, typename Char_= typename LWF::Select::Char<bits>::Type>
struct UTF : Text::Character::Encoding::Traits {
  typedef Char_ Char;
  typedef Text::Character::Encoding::Unicode::Encoder<bits, Char> Encoder;
  typedef Text::Character::Encoding::Unicode::Decoder<bits, Char> Decoder;

  Bool operator == (const UTF &) const { return True; }
  Bool operator != (const UTF &utf) const { return !(*this == utf); }
};

}}}}} // namespace CShift::Text::Character::Encoding::Unicode

#endif // CSHIFT_TEXT_CHARACTER_ENCODING_UNICODE_UTF_H
