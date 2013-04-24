#ifndef CSHIFT_LWF_REFERENCE_INTERFACE_H
#define CSHIFT_LWF_REFERENCE_INTERFACE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Reference {

namespace Traits {

struct Interface {
  virtual ~Interface() {}
  virtual Void IncRef() = 0;
  virtual Void DecRef() = 0;
};

} // namespace Traits

struct Interface : virtual LWF::Reference::Traits::Interface {};

}}} // namespace CShift::LWF::Reference

#endif // CSHIFT_LWF_REFERENCE_INTERFACE_H
