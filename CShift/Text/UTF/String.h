#ifndef CSHIFT_TEXT_UTF_STRING_H
#define CSHIFT_TEXT_UTF_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Collection/Strings/Adjustment.h"
#include "Text/Character/Encoding/Unicode/UTF-8.h"
#include "Text/Character/Encoding/Unicode/UTF-16.h"
#include "Text/Character/Encoding/Unicode/UTF-32.h"


namespace CShift {
namespace Text {

template <UInt bits>
struct UTF : Text::Collection::Strings::Adjustment<
              Text::Character::Encoding::Unicode::UTF<bits> > {};

}} // namespace CShift::Text

#endif // CSHIFT_TEXT_UTF_STRING_H
