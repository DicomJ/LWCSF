#ifndef CSHIFT_LWF_ALGORITHM_DIFFERENT_EXACTLY_H
#define CSHIFT_LWF_ALGORITHM_DIFFERENT_EXACTLY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/Different.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Different {

namespace Traits {

struct Exactly {

  template <typename Iterator, typename From>
  Int operator()(Iterator i, const Iterator &iLast, From j, const From &jLast) const {
  while (i != iLast && j != jLast && *i++ == *j++);
  return
    i == iLast ? (j == jLast ?     0      : (0 - Int(*j))) :
  /*i != iLast*/ (j != jLast ? (*i - *j)  : (0 + Int(*i))) ;
  }
};

} // namespace Traits

typedef LWF::Algorithm::Different::Algorithm<LWF::Algorithm::Different::Traits::Exactly> Exactly;

}}}} // namespace CShift::LWF::Algorithm::Different

#endif // CSHIFT_LWF_ALGORITHM_DIFFERENT_EXACTLY_H
