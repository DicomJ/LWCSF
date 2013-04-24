#ifndef CSHIFT_LWF_TRAITS_IS_HAS_H
#define CSHIFT_LWF_TRAITS_IS_HAS_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"


namespace CShift {
namespace LWF {
namespace Traits {

struct        One { Byte        one[1]; };
struct AnotherOne { Byte anotherOne[sizeof(One) + 1]; };

struct Is  : One {}; struct Isnot  : AnotherOne {};
struct Has : One {}; struct Hasnot : AnotherOne {};

}}} // namespace CShift::Traits

#endif // CSHIFT_LWF_TRAITS_IS_HAS_H
