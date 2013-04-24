#ifndef CSHIFT_TEXT_ASCII_STRING_H
#define CSHIFT_TEXT_ASCII_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Collection/Strings/Adjustment.h"
#include "Text/Character/Encoding/ASCII.h"


namespace CShift {
namespace Text {

struct ASCII : Text::Collection::Strings::Adjustment<
                Text::Character::Encoding::ASCII > {};

}} // namespace CShift::Text::Code

#endif // CSHIFT_TEXT_ASCII_STRING_H
