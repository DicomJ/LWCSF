#ifndef CHSIFT_TEXT_OUTPUT_STREAM_H
#define CHSIFT_TEXT_OUTPUT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "Text/Stream.h"
#include "IOF/Output/Stream.h"

namespace CShift {
namespace Text {
namespace Output {

template <typename Encoding>
struct Stream : virtual Text::Stream<Encoding>,
                        IOF::Output::Stream<typename Encoding::Char> {};

}}} // namespace CShift::Text::Output

#endif // CHSIFT_TEXT_OUTPUT_STREAM_H
