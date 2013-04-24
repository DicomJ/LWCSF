#ifndef CSHIFT_LWF_UNIQUE_BUFFER_H
#define CSHIFT_LWF_UNIQUE_BUFFER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Unique/Array.h"


namespace CShift {
namespace LWF {
namespace Unique {

namespace Traits {

template <typename Deleter = LWF::Deleter<Byte[]> >
struct Buffer : LWF::Unique::Array<Byte, Deleter> {
  private: typedef LWF::Unique::Array<Byte, Deleter> Base;
  public: typedef typename Base::Iterator Iterator;

  Buffer(const Iterator &begin = null, Int size = 0, const Deleter &deleter = Deleter())
    : Base(begin, size, deleter) {}
  Buffer(const Iterator &begin, const Iterator &end, const Deleter &deleter = Deleter())
    : Base(begin, end, deleter) {}
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
  private: typedef LWF::Traits::Nonconst<Base> Nonconst; public:
  operator Nonconst () { return Nonconst(*this); }
  Buffer(Nonconst buffer) : Base(buffer) {}
  Buffer &operator = (Nonconst buffer) { Base::operator = (buffer); return *this; }
  #endif // !C++11

  operator LWF::Weak::Buffer () const {
    return LWF::Weak::Buffer (Base::begin(), Base::end());
  }
};

} // namespace Traits

typedef LWF::Unique::Traits::Buffer<> Buffer;

}}} // namespace CShift::LWF::Unique

#endif // CSHIFT_LWF_UNIQUE_BUFFER_H
