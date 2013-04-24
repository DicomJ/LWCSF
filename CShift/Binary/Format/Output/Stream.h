#ifndef CHSIFT_BINARY_FORMAT_OUTPUT_STREAM_H
#define CHSIFT_BINARY_FORMAT_OUTPUT_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Binary/Format/Stream.h"
#include "IOF/Format/Output/Stream.h"

namespace CShift {
namespace Binary {
namespace Format {
namespace Output {

struct Stream  : virtual Binary::Format::Stream,
                         IOF::Format::Output::Stream {
  typedef LWF::Weak::Const::Buffer Sequence;

  template <typename T>
  Stream &operator << (const T &value) { return (*this) <<= value, *this; }

  virtual operator Bool () const = 0;

  private: virtual Void operator <<= (const  Int   &) = 0;
  private: virtual Void operator <<= (const UInt   &) = 0;
  private: virtual Void operator <<= (const  Int8  &) = 0;
  private: virtual Void operator <<= (const UInt8  &) = 0;
  private: virtual Void operator <<= (const  Int16 &) = 0;
  private: virtual Void operator <<= (const UInt16 &) = 0;
  private: virtual Void operator <<= (const  Int32 &) = 0;
  private: virtual Void operator <<= (const UInt32 &) = 0;
  #if PLATFORM_COMPILER_64BITS_INTEGER
  private: virtual Void operator <<= (const  Int64 &) = 0;
  private: virtual Void operator <<= (const UInt64 &) = 0;
  #endif // PLATFORM_COMPILER_64BITS_INTEGER

  #if PLATFORM_COMPILER_FLOATING_POINT
  private: virtual Void operator <<= (const Float   &) = 0;
  private: virtual Void operator <<= (const Double  &) = 0;
  private: virtual Void operator <<= (const LDouble &) = 0;
  #endif // PLATFORM_COMPILER_FLOATING_POINT

  private: virtual Void operator <<= (const Void *) = 0;

  private: virtual Void operator <<= (const Sequence &) = 0;
};

Void operator <<= (Stream &stream, const Char8 &ch) {
  stream << (UInt8)ch;
}

#if PLATFORM_COMPILER_UCHAR
Void operator <<= (Stream &stream, const Char16 &ch) {
  stream << (UInt16)ch;
}

Void operator <<= (Stream &stream, const Char32 &ch) {
  stream << (UInt32)ch;
}
#endif // PLATFORM_COMPILER_UCHAR

Void operator <<= (Stream &stream, const WChar &ch) {
  stream << (typename LWF::Integer<sizeof(ch), LWF::Kind::Integer::Unsigned>::Type)ch;
}

}}}} // namespace CShift::Binary::Format::Output

namespace CShift {
namespace Binary {
namespace Format {
namespace Output {

namespace Optimize {
namespace String {

template <typename String,
          Bool = sizeof(typename String::Char) ==
                 sizeof(typename Stream::Sequence::Type)>
struct Body {
  Body(Stream &stream, const String &string) {
    stream << Stream::Sequence(string);
  }
};

template <typename String>
struct Body<String, False> {
  Body(Stream &stream, const String &string) {
    for (typename String::Const::Iterator i = string.begin();
         i != string.end() && stream; ++i) { stream << *i; }
  }
};

}} // namespace Optimize::String

template <typename Encoding, typename Base>
Void operator <<= (Stream &stream,
                   const CShift::Text::Collection::String<Encoding, Base> &string) {
  stream << string.size();
  Optimize::String::Body<CShift::Text::Collection::String<Encoding, Base> >(stream, string);
}

}}}} // namespace CShift::Binary::Format::Output

#endif // CHSIFT_BINARY_FORMAT_OUTPUT_STREAM_H
