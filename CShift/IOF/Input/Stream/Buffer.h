#ifndef CHSIFT_IOF_INPUT_STREAM_BUFFER_H
#define CHSIFT_IOF_INPUT_STREAM_BUFFER_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Input/Stream.h"

namespace CShift {
namespace IOF {
namespace Input {

template <typename T>
template <typename Substream, typename Base>
struct Stream<T>::Buffer : virtual IOF::Stream<T>::template Buffer<Substream, Base> {
  typename Base::Const::Iterator begin() const { return Base::begin(); }
  typename Base::Const::Iterator end() const { return Base::end(); }
//  typename Base::Const::Iterator popFront() const { return Base::popFront(); }
};

}}} // namespace CShift::IOF::Input

#endif // CHSIFT_IOF_INPUT_STREAM_BUFFER_H
