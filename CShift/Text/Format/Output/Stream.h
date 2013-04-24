#ifndef CHSIFT_TEXT_FORMAT_OUTPUT_STREAM_H
#define CHSIFT_TEXT_FORMAT_OUTPUT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Format/Stream.h"
#include "IOF/Format/Output/Stream.h"

namespace CShift {
namespace Text {
namespace Format {
namespace Output {

template <typename Encoding>
struct Stream  : virtual Text::Format::Stream<Encoding>,
                         IOF::Format::Output::Stream {

  typedef LWF::Weak::Array<const typename Encoding::Char> Sequence;

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

template <typename Encoding>
Void operator <<= (Stream<Encoding> &stream,
                 const CShift::Text::CString<const typename Encoding::Char> &cstring) {
  stream << typename Stream<Encoding>::Sequence(cstring.range());
}

template <typename Encoding>
Void operator <<= (Stream<Encoding> &stream,
                 const typename Encoding::Char *cstring) {
  stream <<= CShift::Text::cstring(cstring);
}

template <typename Encoding>
Void operator <<= (Stream<Encoding> &stream,
                 const typename Encoding::Char &ch) {
  stream << typename Stream<Encoding>::Sequence(&ch, &ch + 1);
}

}}}} // namespace CShift::Text::Format::Output

namespace CShift {
namespace Text {
namespace Format {
namespace Output {

template <typename Encoding, typename Base>
Void operator <<= (Stream<Encoding> &stream,
                   const CShift::Text::Collection::String<Encoding, Base> &string) {
  stream << typename Stream<Encoding>::Sequence(string.begin(), string.end());
}

template <typename Encoding, typename E, typename B>
Void operator <<= (Stream<Encoding> &stream,
                 const CShift::Text::Collection::String<E, B> &string) {
  stream <<= static_cast<const CShift::Text::Collection::String<Encoding, B> &>(string);
}

}}}} // namespace CShift::Text::Format::Output

#endif // CHSIFT_TEXT_FORMAT_OUTPUT_STREAM_H
