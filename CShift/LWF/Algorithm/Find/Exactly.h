#ifndef CSHIFT_LWF_ALGORITHM_FIND_EXACTLY_H
#define CSHIFT_LWF_ALGORITHM_FIND_EXACTLY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/Find.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Find {

namespace Traits {

struct Exactly {

  template <typename Where, typename What>
  Where operator()(Where whereFirst, const Where &whereLast,
                   const What  &whatFirst , const What  &whatLast) const {
    Where where = whereFirst;
    What what = whatFirst;
    while (where != whereLast) {
      if (what != whatLast) {
        if (*what == *where) {
          ++where; ++what;
        } else {
          where = ++whereFirst; what = whatFirst;
        }
      } else {
        where = whereFirst;
      }
    }
    return where;
  }
};

} // namespace Traits

typedef LWF::Algorithm::Find::Algorithm<LWF::Algorithm::Find::Traits::Exactly> Exactly;

}}}} // namespace CShift::LWF::Algorithm::Find

#endif // CSHIFT_LWF_ALGORITHM_FIND_EXACTLY_H
