#ifndef CHSIFT_BINARY_FORMAT_IO_STREAM_H
#define CHSIFT_BINARY_FORMAT_IO_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "Binary/Format/Input/Stream.h"
#include "Binary/Format/Output/Stream.h"

namespace CShift {
namespace Binary {
namespace Format {
namespace IO {

struct Stream : Binary::Format::Input ::Stream,
                Binary::Format::Output::Stream {};

}}}} // namespace CShift::Binary::Format::IO

#endif // CHSIFT_BINARY_FORMAT_IO_STREAM_H
