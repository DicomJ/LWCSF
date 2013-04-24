#ifndef CSHIFT_LWF_SHORTEST_INTEGER_H
#define CSHIFT_LWF_SHORTEST_INTEGER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Integer.h"


namespace CShift {
namespace LWF {
namespace Shortest {

template <LUInt value, typename Sign = LWF::Kind::Integer::Signed> class Integer {

  template <UInt bytes,
            typename Integer = typename LWF::Integer<bytes, Sign>::Type,
            Bool = value <= LUInt(LWF::Type<Integer>::max) >
  struct Select {
    typedef Integer Type;
  };
  template <UInt bytes, typename Integer>
  struct Select<bytes, Integer, False> {
    typedef typename Select<2 * bytes>::Type Type;
  };

  public: typedef typename Select<sizeof(Int8)>::Type Type;
};

namespace Signed {
template <LUInt value> struct Integer :
    LWF::Shortest::Integer<value, LWF::Kind::Integer::Signed> {};
}
namespace Unsigned {
template <LUInt value> struct Integer :
    LWF::Integer<value, LWF::Kind::Integer::Unsigned> {};
}

}}} // namespace CShift::LWF::Shortest

#endif // CSHIFT_LWF_SHORTEST_INTEGER_H
