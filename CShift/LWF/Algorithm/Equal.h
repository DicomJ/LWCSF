#ifndef CSHIFT_LWF_ALGORITHM_EQUAL_H
#define CSHIFT_LWF_ALGORITHM_EQUAL_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Equal {

template <typename Base>
struct Algorithm : Base {

  template <typename Iterator, typename To>
  Bool operator()(const Iterator &first, const Iterator &last,
                   const To  &toFirst , const To  &toLast) const {
    return Base::operator() (first, last, toFirst, toLast);
  }

  template <typename Range, typename To>
  Bool operator()(const Range &range, const To  &toFirst, const To  &toLast) const {
    return (*this)(range.begin(), range.end(), toFirst, toLast);
  }

  template <typename Iterator, typename To>
  Bool operator()(const Iterator &first, const Iterator &last, const To  &to) const {
    return (*this)(first, last, to.begin(), to.end());
  }

  template <typename Range, typename To>
  Bool operator()(const Range &range, const To &to) const {
    return (*this)(range.begin(), range.end(), to.begin(), to.end());;
  }
};

}}}} // namespace CShift::LWF::Algorithm::Equal

#endif // CSHIFT_LWF_ALGORITHM_EQUAL_H
