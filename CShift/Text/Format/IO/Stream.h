#ifndef CHSIFT_TEXT_FORMAT_IO_STREAM_H
#define CHSIFT_TEXT_FORMAT_IO_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "Text/Format/Input/Stream.h"
#include "Text/Format/Output/Stream.h"

namespace CShift {
namespace Text {
namespace Format {
namespace IO {

template <typename Encoding>
struct Stream : Text::Format::Input ::Stream<Encoding>,
                Text::Format::Output::Stream<Encoding> {};

}}}} // namespace CShift::Text::Format::IO

#endif // CHSIFT_TEXT_FORMAT_IO_STREAM_H
