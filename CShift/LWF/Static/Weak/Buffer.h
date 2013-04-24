#ifndef CSHIFT_LWF_STATIC_WEAK_BUFFER_H
#define CSHIFT_LWF_STATIC_WEAK_BUFFER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Static/Weak/Array.h"


namespace CShift {
namespace LWF {
namespace Static {
namespace Weak {

template <UInt size, typename Type = Byte>
struct Buffer : LWF::Static::Weak::Array<Type, size>
{
  private: typedef LWF::Static::Weak::Array<Type, size> Base;
  public: typedef typename Base::Iterator Iterator;

  Buffer(const Iterator &begin = null) : Base(begin) { }

  Buffer &operator = (const Null &) { Base::operator = (null); return *this; }

  Buffer &operator = (const Buffer &buffer) {
    Base::operator = (buffer); return *this;
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Buffer &operator = (Buffer &&buffer) {
    Base::operator = (LWF::Forward::reference<Buffer>(buffer)); return *this;
  }
  #endif // C++11

  operator LWF::Static::Weak::Buffer<size, const Byte> () const {
    return LWF::Static::Weak::Buffer<size, const Byte> (Base::begin());
  }
};

}}}} // namespace CShift::LWF::Static::Weak

#endif // CSHIFT_LWF_STATIC_WEAK_BUFFER_H
