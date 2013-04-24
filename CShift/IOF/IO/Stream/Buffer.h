#ifndef CHSIFT_IOF_IO_STREAM_BUFFER_H
#define CHSIFT_IOF_IO_STREAM_BUFFER_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/IO/Stream.h"

namespace CShift {
namespace IOF {
namespace IO {

template <typename T>
template <typename Substream, typename Base>
struct Stream<T>::Buffer :
    IOF::Input ::Stream<T>::template Buffer<Substream, Base>,
    IOF::Output::Stream<T>::template Buffer<Substream, Base> {};

}}} // namespace CShift::IOF::IO

#endif // CHSIFT_IOF_IO_STREAM_BUFFER_H
