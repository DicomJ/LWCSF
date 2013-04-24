#ifndef CHSIFT_BINARY_IO_STREAM_H
#define CHSIFT_BINARY_IO_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "Binary/Input/Stream.h"
#include "Binary/Output/Stream.h"

namespace CShift {
namespace Binary {
namespace IO {

struct Stream : Binary::Input ::Stream,
                Binary::Output::Stream {};

}}} // namespace CShift::Binary::IO

#endif // CHSIFT_BINARY_IO_STREAM_H
