#ifndef CSHIFT_LWF_STATIC_UNIQUE_BUFFER_H
#define CSHIFT_LWF_STATIC_UNIQUE_BUFFER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Static/Unique/Array.h"
#include "LWF/Static/Weak/Buffer.h"

namespace CShift {
namespace LWF {
namespace Static {
namespace Unique {

template <UInt size, typename Deleter = LWF::Deleter<Byte[]> >
struct Buffer : LWF::Static::Unique::Array<Byte, size, Deleter>
{
  private: typedef LWF::Static::Unique::Array<Byte, size, Deleter> Base;
  public: typedef typename Base::Iterator Iterator;

  Buffer(const Iterator &begin = null, const Deleter &deleter = Deleter())
    : Base(begin, deleter) { }
  Buffer(const Deleter &deleter) : Base(deleter) {}

  Buffer &operator = (const Null &) { Base::operator = (null); return *this; }

  Buffer(Buffer &buffer) : Base(buffer) {}
  Buffer &operator = (Buffer &buffer) { Base::operator = (buffer); return *this; }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Buffer(Buffer &&buffer) : Base(LWF::Forward::reference<Base>(buffer)) {}
  Buffer &operator = (Buffer &&buffer) {
    Base::operator = (LWF::Forward::reference<Base>(buffer)); return *this;
  }
  #else // !C++11
  protected: typedef LWF::Traits::Nonconst<Base> Nonconst; public:
  operator Nonconst () { return Nonconst(*this); }
  Buffer(Nonconst buffer) : Base(buffer) {}
  Buffer &operator = (Nonconst buffer) { Base::operator = (buffer); return *this; }
  #endif // !C++11*/

  operator LWF::Static::Weak::Buffer<size> () const {
    return LWF::Static::Weak::Buffer<size> (Base::begin());
  }
  operator LWF::Static::Weak::Buffer<size, const Byte> () const {
    return LWF::Static::Weak::Buffer<size, const Byte> (Base::begin());
  }
};

}}}} // namespace CShift::LWF::Static::Unique

#endif // CSHIFT_LWF_STATIC_UNIQUE_BUFFER_H
