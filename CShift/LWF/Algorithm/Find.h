#ifndef CSHIFT_LWF_ALGORITHM_FIND_H
#define CSHIFT_LWF_ALGORITHM_FIND_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Algorithm {
namespace Find {

template <typename Base>
struct Algorithm : Base {

  template <typename Where, typename What>
  Where operator()(const Where &whereFirst, const Where &whereLast,
                   const What  &whatFirst , const What  &whatLast) const {
    return Base::operator() (whereFirst, whereLast, whatFirst, whatLast);
  }

  template <typename Where, typename What>
  typename Where::Const::Iterator operator()(const Where &where,
                   const What  &whatFirst, const What  &whatLast) const {
    return (*this)(where.begin(), where.end(), whatFirst, whatLast);
  }

  template <typename Where, typename What>
  Where operator()(const Where &whereFirst, const Where &whereLast,
                   const What  &what) const {
    return (*this)(whereFirst, whereLast, what.begin(), what.end());
  }

  template <typename Where, typename What>
  typename Where::Const::Iterator operator()(const Where &where, const What &what) const {
    return (*this)(where.begin(), where.end(), what.begin(), what.end());;
  }
};

}}}} // namespace CShift::LWF::Algorithm::Find

#endif // CSHIFT_LWF_ALGORITHM_FIND_H
