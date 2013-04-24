#ifndef CHSIFT_IOF_STREAM_H
#define CHSIFT_IOF_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

namespace CShift {
namespace IOF {

template <typename T>
struct Stream {
  template <typename Substream, typename Base> struct Buffer;
};

}} // namespace CShift::IOF

#endif // CHSIFT_IOF_STREAM_H
