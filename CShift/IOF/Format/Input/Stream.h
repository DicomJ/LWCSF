#ifndef CHSIFT_IOF_FORMAT_INPUT_STREAM_H
#define CHSIFT_IOF_FORMAT_INPUT_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Format/Stream.h"

namespace CShift {
namespace IOF {
namespace Format {
namespace Input {

struct Stream  : virtual IOF::Format::Stream {
  private: virtual Void operator >>= ( Int   &) = 0;
  private: virtual Void operator >>= (UInt   &) = 0;
  private: virtual Void operator >>= ( Int8  &) = 0;
  private: virtual Void operator >>= (UInt8  &) = 0;
  private: virtual Void operator >>= ( Int16 &) = 0;
  private: virtual Void operator >>= (UInt16 &) = 0;
  private: virtual Void operator >>= ( Int32 &) = 0;
  private: virtual Void operator >>= (UInt32 &) = 0;
  #if PLATFORM_COMPILER_64BITS_INTEGER
  private: virtual Void operator >>= ( Int64 &) = 0;
  private: virtual Void operator >>= (UInt64 &) = 0;
  #endif // PLATFORM_COMPILER_64BITS_INTEGER

  #if PLATFORM_COMPILER_FLOATING_POINT
  private: virtual Void operator >>= (Float   &) = 0;
  private: virtual Void operator >>= (Double  &) = 0;
  private: virtual Void operator >>= (LDouble &) = 0;
  #endif // PLATFORM_COMPILER_FLOATING_POINT

  private: virtual Void operator >>= (Void * &) = 0;
};

}}}} // namespace CShift::IOF::Format::Input

#endif // CHSIFT_IOF_FORMAT_INPUT_STREAM_H
