#ifndef CSHIFT_TEXT_WIDE_STRING_H
#define CSHIFT_TEXT_WIDE_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Collection/Strings/Adjustment.h"
#include "Text/Character/Encoding/Unicode/Wide.h"


namespace CShift {
namespace Text {

struct Wide : Text::Collection::Strings::Adjustment<
                Text::Character::Encoding::Unicode::Wide > {};

}} // namespace CShift::Text

#endif // CSHIFT_TEXT_WIDE_STRING_H
