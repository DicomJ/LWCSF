#ifndef CSHIFT_LWF_REFERENCE_IMPLEMENTATION_H
#define CSHIFT_LWF_REFERENCE_IMPLEMENTATION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Reference/Interface.h"


namespace CShift {
namespace LWF {
namespace Reference {

namespace Traits {

template <typename Counter>
struct Implementation : virtual LWF::Reference::Interface {
  virtual Void IncRef() { ++counter; }
  virtual Void DecRef() { if (0 == --counter) { delete this; } }
  protected: Implementation() : counter(1) {}
  protected: Counter counter;
};

} // namespace Traits

struct Implementation : LWF::Reference::Traits::Implementation<UInt> {};

}}} // namespace CShift::LWF::Reference

#endif // CSHIFT_LWF_REFERENCE_IMPLEMENTATION_H
