#ifndef CSHIFT_TEXT_STREAM_H
#define CSHIFT_TEXT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "IOF/Stream.h"

namespace CShift {
namespace Text {

template <typename Encoding>
struct Stream : virtual IOF::Stream<typename Encoding::Char> {};

}} // namespace CShift::Text

#endif // CSHIFT_TEXT_STREAM_H
