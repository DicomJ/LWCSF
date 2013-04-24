#ifndef CHSIFT_IOF_OUTPUT_STREAM_BUFFER_H
#define CHSIFT_IOF_OUTPUT_STREAM_BUFFER_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Output/Stream.h"

namespace CShift {
namespace IOF {
namespace Output {

template <typename T>
template <typename Substream, typename Base>
struct Stream<T>::Buffer : virtual IOF::Stream<T>::template Buffer<Substream, Base> {
//  void pushBack  () const { return Base::pushBack(); }
};

}}} // namespace CShift::IOF::Output

#endif // CHSIFT_IOF_OUTPUT_STREAM_BUFFER_H
