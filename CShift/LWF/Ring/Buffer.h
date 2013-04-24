#ifndef CSHIFT_LWF_RING_BUFFER_H
#define CSHIFT_LWF_RING_BUFFER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Ring/Vector.h"


namespace CShift {
namespace LWF {
namespace Ring {

namespace Traits {

template <typename Allocator = LWF::Collection::Ring::Vector::Allocator<Byte> >
struct Buffer :  LWF::Ring::Vector<Byte, Allocator> {
  private: typedef LWF::Ring::Vector<Byte, Allocator> Base; public:

  Buffer(const Allocator &allocator = Allocator()) : Base(allocator) {}

  Buffer(UInt count, const Byte &value = Byte(0),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  Buffer(const Iterator &first, const Iterator &last,
         const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  Buffer(const Range &range, const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  Buffer &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Buffer(const LWF::Initializer::List<Byte> &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  Buffer &operator = (const LWF::Initializer::List<Byte> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  Buffer (const Buffer &buffer, const Allocator &allocator = Allocator())
    : Base(buffer, allocator) {}

  Buffer &operator = (const Buffer &buffer) {
    Base::operator = (buffer);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Buffer(Buffer &&buffer) : Base(LWF::Forward::reference<Base>(buffer)) {}

  Buffer &operator = (Buffer &&buffer) {
    Base::operator = (LWF::Forward::reference<Base>(buffer));
    return *this;
  }
  #endif // C++11
};

} // namespace Traits

typedef LWF::Ring::Traits::Buffer<> Buffer;

}}} // namespace CShift::LWF::Ring

#endif // CSHIFT_LWF_RING_BUFFER_H
