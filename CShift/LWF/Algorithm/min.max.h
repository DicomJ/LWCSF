#ifndef CSHIFT_LWF_ALGORITHM_MIN_MAX_H
#define CSHIFT_LWF_ALGORITHM_MIN_MAX_H

#include "LWF/License"
#include "Author/Andriy.Bulka"


namespace CShift {
namespace LWF {
namespace Algorithm {

#if defined(min)
# undef min
#endif
#if defined(max)
# undef max
#endif

template <typename Type>
Type min(const Type &a, const Type &b) { return a < b ? a : b; }

template <typename Type>
Type max(const Type &a, const Type &b) { return a > b ? a : b; }

} // namespace Algorithm

using Algorithm::min;
using Algorithm::max;

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ALGORITHM_MIN_MAX_H
