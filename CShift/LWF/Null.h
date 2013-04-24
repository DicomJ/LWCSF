#ifndef CSHIFT_LWF_NULL_H
#define CSHIFT_LWF_NULL_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace LWF {

struct Null {
  template <typename U>
  Bool operator == (const U &u) const { return   u == *this;  }
  template <typename U>
  Bool operator != (const U &u) const { return !(*this == u); }

  Bool operator == (const Null &    ) const { return True; }
  Bool operator != (const Null &null) const { return !(*this == null);   }

  template <typename T>
  operator T * () const { return (T *)0; }

} const null = null;

using LWF::Null;

}} // namespace CShift::LWF

namespace CShift {

using LWF::Null;
using LWF::null;

} // namespace CShift


#endif // CSHIFT_LWF_NULL_H
