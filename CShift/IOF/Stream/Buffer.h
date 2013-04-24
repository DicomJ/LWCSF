#ifndef CHSIFT_IOF_STREAM_BUFFER_H
#define CHSIFT_IOF_STREAM_BUFFER_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Stream.h"

namespace CShift {
namespace IOF {

template <typename T>
template <typename Substream, typename Base>
struct Stream<T>::Buffer {};

}} // namespace CShift::IOF

#endif // CHSIFT_IOF_STREAM_BUFFER_H
