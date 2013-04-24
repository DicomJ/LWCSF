#ifndef CHSIFT_IOF_FORMAT_OUTPUT_STREAM_H
#define CHSIFT_IOF_FORMAT_OUTPUT_STREAM_H

#include "IOF/License"
#include "Author/Andriy.Bulka"

#include "IOF/Format/Stream.h"

namespace CShift {
namespace IOF {
namespace Format {
namespace Output {

struct Stream : virtual IOF::Format::Stream {
  private: virtual Void operator <<= (const  Int   &) = 0;
  private: virtual Void operator <<= (const UInt   &) = 0;
  private: virtual Void operator <<= (const  Int8  &) = 0;
  private: virtual Void operator <<= (const UInt8  &) = 0;
  private: virtual Void operator <<= (const  Int16 &) = 0;
  private: virtual Void operator <<= (const UInt16 &) = 0;
  private: virtual Void operator <<= (const  Int32 &) = 0;
  private: virtual Void operator <<= (const UInt32 &) = 0;
  #if PLATFORM_COMPILER_64BITS_INTEGER
  private: virtual Void operator <<= (const UInt64 &) = 0;
  private: virtual Void operator <<= (const  Int64 &) = 0;
  #endif // PLATFORM_COMPILER_64BITS_INTEGER

  #if PLATFORM_COMPILER_FLOATING_POINT
  private: virtual Void operator <<= (const Float   &) = 0;
  private: virtual Void operator <<= (const Double  &) = 0;
  private: virtual Void operator <<= (const LDouble &) = 0;
  #endif // PLATFORM_COMPILER_FLOATING_POINT

  private: virtual Void operator <<= (const Void *) = 0;
};

}}}} // namespace CShift::IOF::Format::Output

#endif // CHSIFT_IOF_FORMAT_OUTPUT_STREAM_H
