#ifndef CHSIFT_BINARY_INPUT_STREAM_H
#define CHSIFT_BINARY_INPUT_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "Binary/Stream.h"
#include "IOF/Input/Stream.h"

namespace CShift {
namespace Binary {
namespace Input {

struct Stream  : virtual Binary::Stream,
                         IOF::Input::Stream<Byte> {};

}}} // namespace CShift::Binary::Input

#endif // CHSIFT_BINARY_INPUT_STREAM_H
