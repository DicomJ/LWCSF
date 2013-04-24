#ifndef CSHIFT_LWF_TRAITS_PREDICTION_H
#define CSHIFT_LWF_TRAITS_PREDICTION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace LWF {
namespace Traits {

template<Bool prediction>
struct Prediction;
template<>
struct Prediction<False> {};
template<>
struct Prediction<True> { struct Type { Type(const Null & = null) {} }; };

}}} // namespace CShift::Traits

#endif // CSHIFT_LWF_TRAITS_PREDICTION_H
