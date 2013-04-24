#ifndef CHSIFT_TEXT_FORMAT_INPUT_STREAM_H
#define CHSIFT_TEXT_FORMAT_INPUT_STREAM_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Text/Format/Stream.h"
#include "IOF/Format/Input/Stream.h"

namespace CShift {
namespace Text {
namespace Format {
namespace Input {

template <typename Encoding>
struct Stream : virtual Text::Format::Stream<Encoding>,
                        IOF::Format::Input::Stream {
  typedef typename Encoding::Char Char;
  typedef LWF::Weak::Array<Char> Sequence;

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

  public: virtual Bool operator >>= (Sequence &) = 0; // returns True if it stops due to sequence overflow
  public: virtual Void get(Sequence &, const Char &) = 0;
};


template <typename Encoding>
Void operator >>= (Stream<Encoding> &stream, typename Encoding::Char &ch) {
  typename Stream<Encoding>::Sequence chr(&ch, ch + 1); stream >> chr;
}


}}}} // namespace CShift::Text::Format::Input

namespace CShift {
namespace Text {
namespace Format {
namespace Input {

template <typename Encoding, typename Base>
Void operator >>= (Stream<Encoding> &stream, CShift::Text::Collection::String<Encoding, Base> &string) {
  typename Encoding::Char buffer[128];
  Bool overflow = True;
  while (overflow && stream) {
    typename Stream<Encoding>::Sequence sequence(buffer, buffer + LWF::countof(buffer));
    overflow = (stream >>= sequence);
    string += sequence;
  }
}

template <typename Encoding, typename E, typename B>
Void operator >>= (Stream<Encoding> &stream,
                 CShift::Text::Collection::String<E, B> &estring) {
  CShift::Text::Collection::String<Encoding, B> string;
  (stream >>= string);
  estring = string;
}

}}}} // namespace CShift::Text::Format::Input

#endif // CHSIFT_TEXT_FORMAT_INPUT_STREAM_H
