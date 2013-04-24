#ifndef CHSIFT_BINARY_FORMAT_INPUT_STREAM_H
#define CHSIFT_BINARY_FORMAT_INPUT_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Binary/Format/Stream.h"
#include "IOF/Format/Input/Stream.h"

namespace CShift {
namespace Binary {
namespace Format {
namespace Input {

struct Stream  : virtual Binary::Format::Stream,
                         IOF::Format::Input::Stream {
  typedef LWF::Weak::Buffer Sequence;

  template <typename T>
  Stream &operator >> (T &value) { return (*this) >>= value, *this; }

  virtual operator Bool () const = 0;

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

  private: virtual Void operator >>= (Sequence &) = 0;
};

Void operator >>= (Stream &stream, Char8 &ch) {
  stream >> (UInt8 &)ch;
}

#if PLATFORM_COMPILER_UCHAR
Void operator >>= (Stream &stream, Char16 &ch) {
  stream >> (UInt16 &)ch;
}

Void operator >>= (Stream &stream, Char32 &ch) {
  stream >> (UInt32 &)ch;
}
#endif // PLATFORM_COMPILER_UCHAR

Void operator >>= (Stream &stream, WChar &ch) {
 stream >> (typename LWF::Integer<sizeof(ch), LWF::Kind::Integer::Unsigned>::Type &)ch;
}

}}}} // namespace CShift::Binary::Format::Input


namespace CShift {
namespace Binary {
namespace Format {
namespace Input {

namespace Optimize {
namespace String {

template <typename String,
          Bool = sizeof(typename String::Char) ==
                 sizeof(typename Stream::Sequence::Type)>
struct Body {
  Body(Stream &stream, String &string, UInt size) {
    Stream::Sequence sequence(string.end(), string.end() + size);
    stream >> sequence;
    string.pushBack(sequence);
  }
};

template <typename String>
struct Body<String, False> {
  Body(Stream &stream, String &string, UInt size) {
    for (; size != -1 && stream; --size) {
      typename String::Char ch; stream >> ch; string.pushBack(ch);
    }
  }
};

}} // namespace Optimize::String

template <typename Encoding, typename Base>
Void operator >>= (Stream &stream,
                   CShift::Text::Collection::String<Encoding, Base> &string) {
  UInt size = 0; const UInt max = LWF::Type<Int16>::max;
  stream >> size;
  if (size > max) { LWF::Exception::Throw(LWF::OutOfRange::Exception()); }
  else {
    string.ensureBackCapacity(size);
    Optimize::String::Body<CShift::Text::Collection::String<Encoding, Base> >(
          stream, string, size);
  }
}

}}}} // namespace CShift::Binary::Format::Input

#endif // CHSIFT_BINARY_FORMAT_INPUT_STREAM_H
