#ifndef CSHIFT_TEXT_FORMAT_STREAM_H
#define CSHIFT_TEXT_FORMAT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "IOF/Format/Stream.h"

namespace CShift {
namespace Text {
namespace Format {

template <typename Encoding>
struct Stream : virtual IOF::Format::Stream {};

}}} // namespace CShift::Text::Format

#endif // CSHIFT_TEXT_FORMAT_STREAM_H
