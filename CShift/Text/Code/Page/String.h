#ifndef CSHIFT_TEXT_CODE_PAGE_STRING_H
#define CSHIFT_TEXT_CODE_PAGE_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Collection/Strings/Adjustment.h"
#include "Text/Character/Encoding/Code/Page.h"


namespace CShift {
namespace Text {
namespace Code {

struct Page : Text::Collection::Strings::Adjustment<
                Text::Character::Encoding::Code::Page > {};

}}} // namespace CShift::Text::Code

#endif // CSHIFT_TEXT_CODE_PAGE_STRING_H
