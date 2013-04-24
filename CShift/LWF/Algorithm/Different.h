#ifndef CSHIFT_LWF_ALGORITHM_DIFFERENT_H
#define CSHIFT_LWF_ALGORITHM_DIFFERENT_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Different {

template <typename Base>
struct Algorithm : Base {

  template <typename Iterator, typename From>
  Int operator()(const Iterator &first, const Iterator &last,
                   const From  &fromFirst , const From  &fromLast) const {
    return Base::operator() (first, last, fromFirst, fromLast);
  }

  template <typename Range, typename From>
  Int operator()(const Range &range, const From  &fromFirst, const From  &fromLast) const {
    return (*this)(range.begin(), range.end(), fromFirst, fromLast);
  }

  template <typename Iterator, typename From>
  Int operator()(const Iterator &first, const Iterator &last, const From  &from) const {
    return (*this)(first, last, from.begin(), from.end());
  }

  template <typename Range, typename From>
  Int operator()(const Range &range, const From &from) const {
    return (*this)(range.begin(), range.end(), from.begin(), from.end());;
  }
};

}}}} // namespace CShift::LWF::Algorithm::Different

#endif // CSHIFT_LWF_ALGORITHM_DIFFERENT_H
