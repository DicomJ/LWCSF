#ifndef CHSIFT_IOF_IO_STREAM_H
#define CHSIFT_IOF_IO_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Input/Stream.h"
#include "IOF/Output/Stream.h"

namespace CShift {
namespace IOF {
namespace IO {

template <typename T>
struct Stream : IOF::Input ::Stream<T>,
                IOF::Output::Stream<T> {

  template <typename Substream, typename Base> struct Buffer;
};

}}} // namespace CShift::IOF::IO

#endif // CHSIFT_IOF_IO_STREAM_H
