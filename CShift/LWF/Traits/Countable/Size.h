#ifndef CSHIFT_LWF_TRAITS_COUNTABLE_SIZE_H
#define CSHIFT_LWF_TRAITS_COUNTABLE_SIZE_H


namespace CShift {
namespace LWF {
namespace Traits {
namespace Countable {

template <Bool countable>
struct Size {
  Size &operator ++() { ++counter; return *this; }
  Size &operator --() { --counter; return *this; }

  UInt size() const { return counter; }

  Size &operator -= (UInt count) { counter -= count; return *this; }
  Size &operator += (UInt count) { counter += count; return *this; }

  Size &operator = (UInt count) { counter = count; return *this; }

  Size(UInt counter_ = 0) : counter(counter_) { }
  private: UInt counter;
};

template <>
struct Size<False> {
  Size &operator ++() { return *this; }
  Size &operator --() { return *this; }

  Size &operator -= (UInt) { return *this; }
  Size &operator += (UInt) { return *this; }

  Size &operator = (UInt) { return *this;}

  Size(UInt = 0) {}
};

}}}} // namespace CShift::LWF::Traits::Countable

#endif // CSHIFT_LWF_TRAITS_COUNTABLE_SIZE_H
