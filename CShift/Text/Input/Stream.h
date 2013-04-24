#ifndef CHSIFT_TEXT_INPUT_STREAM_H
#define CHSIFT_TEXT_INPUT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "Text/Stream.h"
#include "IOF/Input/Stream.h"

namespace CShift {
namespace Text {
namespace Input {

template <typename Encoding>
struct Stream : virtual Text::Stream<Encoding>,
                        IOF::Input::Stream<typename Encoding::Char> {};

}}} // namespace CShift::Text::Input

#endif // CHSIFT_TEXT_INPUT_STREAM_H
