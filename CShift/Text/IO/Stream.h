#ifndef CHSIFT_TEXT_IO_STREAM_H
#define CHSIFT_TEXT_IO_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "Text/Input/Stream.h"
#include "Text/Output/Stream.h"

namespace CShift {
namespace Text {
namespace IO {

template <typename Encoding>
struct Stream : Text::Input::Stream<Encoding>,
                Text::Output::Stream<Encoding> {};

}}} // namespace CShift::Text::IO

#endif // CHSIFT_TEXT_IO_STREAM_H
