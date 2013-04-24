#ifndef CSHIFT_LWF_ALGORITHM_SWAP_H
#define CSHIFT_LWF_ALGORITHM_SWAP_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Value/swap.h"


namespace CShift {
namespace LWF {
namespace Algorithm {

template <typename T>
Void swap(T &a, T &b) { LWF::Value<T>(a).swap(b); }

} // namespace Algorithm

using Algorithm::swap;

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ALGORITHM_SWAP_H
