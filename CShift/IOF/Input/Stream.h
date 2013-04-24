#ifndef CHSIFT_IOF_INPUT_STREAM_H
#define CHSIFT_IOF_INPUT_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Stream.h"
#include "LWF/Type.h"
#include "LWF/Weak/Array.h"

namespace CShift {
namespace IOF {
namespace Input {

template <typename T>
struct Stream : virtual IOF::Stream<T> {

  template <typename Substream, typename Base> struct Buffer;

  virtual operator Bool() = 0;

  virtual UInt read(LWF::Weak::Array<T>) = 0;
};

}}} // namespace CShift::IOF::Input

#endif // CHSIFT_IOF_INPUT_STREAM_H
