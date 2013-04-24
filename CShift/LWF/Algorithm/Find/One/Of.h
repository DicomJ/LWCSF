#ifndef CSHIFT_LWF_ALGORITHM_FIND_ONE_OF_H
#define CSHIFT_LWF_ALGORITHM_FIND_ONE_OF_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Range.h"
#include "LWF/Algorithm/Find.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Find {

namespace Traits {
namespace One {

struct Of {

  template <typename Where, typename What>
  Where operator()(Where whereFirst, const Where &whereLast,
                   const What  &whatFirst , const What  &whatLast) const {
    for (;whereFirst != whereLast &&
         !LWF::range(whatFirst, whatLast).contains(*whereFirst); ++whereFirst) {
    } return whereFirst;
  }
};

} // namespace One
} // namespace Traits

namespace One {
typedef LWF::Algorithm::Find::Algorithm<LWF::Algorithm::Find::Traits::One::Of> Of;
} // namespace One

}}}} // namespace CShift::LWF::Algorithm::Find

#endif // CSHIFT_LWF_ALGORITHM_FIND_ONE_OF_H
