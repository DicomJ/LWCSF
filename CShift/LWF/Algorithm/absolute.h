#ifndef CSHIFT_LWF_ALGORITHM_ABSOLUTE_H
#define CSHIFT_LWF_ALGORITHM_ABSOLUTE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Algorithm {

template <typename Type>
UInt absolute(const Type &a) { return a < 0 ? -a : a; }

} // namespace Algorithm

using Algorithm::absolute;

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ALGORITHM_ABSOLUTE_H
