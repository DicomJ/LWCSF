#ifndef CSHIFT_LWF_TYPE_CAST_H
#define CSHIFT_LWF_TYPE_CAST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Prototype.h"
#include "LWF/Traits/Lame.h"
#include "LWF/Traits/Match/Type.h"
#include "LWF/Traits/Type.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Cast {

namespace By {

template <typename From, typename To,
          typename K = typename LWF::Traits::Type<From>::Kind>
struct Kind {
  static const Bool isCastible =
    LWF::Traits::Match::Type<typename LWF::Traits::Type<From>::Kind,
                             typename LWF::Traits::Type<To>::Kind>::equal;
};

} // namespace By

namespace As {

template <typename From, typename To,
          typename Kind = typename LWF::Traits::Type<To>::Kind>
struct Pointer {
  static const Bool isCastible = false;
};

} // namespace As

namespace As {

namespace Kind {

template <typename From, typename To,
          typename Kind = typename LWF::Traits::Type<To>::Kind>
struct Value {
  static const Bool isCastible = By::Kind<From, To>::isCastible &&
                                 sizeof(From) == sizeof(To);
};

template <typename From, typename To>
struct Value <From, To, LWF::Kind::Nonfundamental> : By::Kind<From, To> {};

} // namespace Kind

namespace Same {
namespace Kind {

template <typename From, typename To,
          Bool sameKind =
            LWF::Traits::Match::Type<typename LWF::Traits::Type<From>::Kind,
                                     typename LWF::Traits::Type<To>::Kind>::equal>
struct Value {
  static const Bool isCastible = false;
};

template <typename From, typename To>
struct Value<From, To, true> : As::Kind::Value<From, To> {};

}} // namespace Same::Kind

template <typename From, typename To, typename Kind = typename LWF::Traits::Type<From>::Kind>
struct Value  : Same::Kind::Value<From, To> {};

template <typename From, typename To>
struct Value<From, To, LWF::Kind::Pointer> : As::Pointer<From, To> {};

} // namespace As

namespace As {

template <typename From, typename To>
struct Pointer<From, To, LWF::Kind::Pointer> {

  static const Bool isCastible =
      LWF::Traits::Type<From>::subscriptible ==
        LWF::Traits::Type<To>::subscriptible &&
      As::Value<typename LWF::Traits::Type<From>::Value::Type,
                typename LWF::Traits::Type<To>::Value::Type>::isCastible;
};

} // namespace As

namespace By {

  template <typename From, typename To>
  struct Kind<From, To, LWF::Kind::Nonfundamental> {
  static const Bool isCastible =
     LWF::Traits::Castable::Types<From, To>::byOperator;
  };

  template <typename From, typename To>
  struct Kind<From, To, LWF::Kind::Pointer> : As::Pointer<From, To>{};
} // namespace By

}}}} // namespace CShift::LWF::Traits::Cast

#endif // CSHIFT_LWF_TYPE_CAST_H
