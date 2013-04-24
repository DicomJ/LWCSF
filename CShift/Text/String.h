#ifndef CSHIFT_TEXT_STRING_H
#define CSHIFT_TEXT_STRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

// TODO: Make this part of file a platform depended
#include "Text/ASCII/String.h"

namespace CShift {
namespace Text {
  typedef Text::ASCII Default;
}} // namespace CShift::Text
//  ENDTODO

namespace CShift {
namespace Text {

typedef Text::Default::String String;
typedef Text::Default::Encoding Encoding;

}} // namespace CShift::Text

#endif // CSHIFT_TEXT_STRING_H
