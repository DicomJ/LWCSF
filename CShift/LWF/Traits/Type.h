#ifndef CSHIFT_LWF_TRAITS_TYPE_H
#define CSHIFT_LWF_TRAITS_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"

namespace CShift {
namespace LWF {
namespace Traits {

template <typename T>
struct Type : Platform::Hardware::Type::Traits<T> {};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_TYPE_H
