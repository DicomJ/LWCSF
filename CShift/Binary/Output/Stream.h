#ifndef CHSIFT_BINARY_OUTPUT_STREAM_H
#define CHSIFT_BINARY_OUTPUT_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "Binary/Stream.h"
#include "IOF/Output/Stream.h"

namespace CShift {
namespace Binary {
namespace Output {

struct Stream  : virtual Binary::Stream,
                         IOF::Output::Stream<Byte> {};

}}} // namespace CShift::Binary::Output

#endif // CHSIFT_BINARY_OUTPUT_STREAM_H
