#ifndef CHSIFT_IOF_FORMAT_IO_STREAM_H
#define CHSIFT_IOF_FORMAT_IO_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Format/Input/Stream.h"
#include "IOF/Format/Output/Stream.h"

namespace CShift {
namespace IOF {
namespace Format {
namespace IO {

struct Stream : IOF::Format::Input ::Stream,
                IOF::Format::Output::Stream {};

}}}} // namespace CShift::IOF::Format::IO

#endif // CHSIFT_IOF_FORMAT_IO_STREAM_H
