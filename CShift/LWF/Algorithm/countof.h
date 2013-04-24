#ifndef CSHIFT_LWF_ALGORITHM_COUNTOF_H
#define CSHIFT_LWF_ALGORITHM_COUNTOF_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Algorithm {

template <typename Type>
UInt countof(const Type &a) { return sizeof(a)/sizeof(a[0]); }

} // namespace Algorithm

using Algorithm::countof;

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ALGORITHM_COUNTOF_H
