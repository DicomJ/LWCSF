#ifndef CSHIFT_LWF_ALGORITHM_EQUAL_EXACTLY_H
#define CSHIFT_LWF_ALGORITHM_EQUAL_EXACTLY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/Equal.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Equal {

namespace Traits {

struct Exactly {

  template <typename Iterator, typename To>
  Bool operator()(Iterator i, const Iterator &iLast, To j, const To &jLast) const {
    while (i != iLast && j != jLast && *i++ == *j++);
    return i == iLast && j == jLast;
  }
};

} // namespace Traits

typedef LWF::Algorithm::Equal::Algorithm<LWF::Algorithm::Equal::Traits::Exactly> Exactly;

}}}} // namespace CShift::LWF::Algorithm::Equal

#endif // CSHIFT_LWF_ALGORITHM_EQUAL_EXACTLY_H
