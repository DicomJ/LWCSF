#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Bits.h"

namespace CShift {
namespace LWF {
namespace Traits {

template <>
const UInt Bits<1>::Debruijn::least[] =
{ 0, 1, 2, 4, 7, 3, 6, 5, };
template <>
const UInt Bits<1>::Debruijn::most[] =
{ 8, 7, 6, 4, 1, 5, 2, 3, };

template <>
const UInt Bits<2>::Debruijn::least[] =
{  0,  1,  2,  5,  3,  9,  6, 11, 15,  4,  8, 10, 14,  7, 13, 12, };
template <>
const UInt Bits<2>::Debruijn::most[] =
{ 16, 15, 14, 11, 13,  7, 10,  5,  1, 12,  8,  6,  2,  9,  3,  4, };

template <>
const UInt Bits<4>::Debruijn::least[] =
{  0,  1,  2,  6,  3, 11,  7, 16,  4, 14, 12, 21,  8, 23, 17, 26,
  31,  5, 10, 15, 13, 20, 22, 25, 30,  9, 19, 24, 29, 18, 28, 27, };
template <>
const UInt Bits<4>::Debruijn::most[] =
{ 32, 31, 30, 26, 29, 21, 25, 16, 28, 18, 20, 11, 24,  9, 15,  6,
   1, 27, 22, 17, 19, 12, 10,  7,  2, 23, 13,  8,  3, 14,  4,  5, };

#if PLATFORM_COMPILER_64BITS_INTEGER
template <>
const UInt Bits<8>::Debruijn::least[] =
{  0,  1,  2,  7,  3, 13,  8, 19,  4, 25, 14, 28,  9, 34, 20, 40,
   5, 17, 26, 38, 15, 46, 29, 48, 10, 31, 35, 54, 21, 50, 41, 57,
  63,  6, 12, 18, 24, 27, 33, 39, 16, 37, 45, 47, 30, 53, 49, 56,
  62, 11, 23, 32, 36, 44, 52, 55, 61, 22, 43, 51, 60, 42, 59, 58, };
template <>
const UInt Bits<8>::Debruijn::most[] =
{ 64, 63, 62, 57, 61, 51, 56, 45, 60, 39, 50, 36, 55, 30, 44, 24,
  59, 47, 38, 26, 49, 18, 35, 16, 54, 33, 29, 10, 43, 14, 23,  7,
   1, 58, 52, 46, 40, 37, 31, 25, 48, 27, 19, 17, 34, 11, 15,  8,
   2, 53, 41, 32, 28, 20, 12,  9,  3, 42, 21, 13,  4, 22,  5,  6, };
#endif //PLATFORM_COMPILER_64BITS_INTEGER

}}} // namespace CShift::LWF::Traits
