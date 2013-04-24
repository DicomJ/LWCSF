#ifndef CSHIFT_LWF_TRAITS_SUBSCRIPTABLE_PTR_H
#define CSHIFT_LWF_TRAITS_SUBSCRIPTABLE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Plain/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Subscriptable {

template <typename T>
struct Ptr : LWF::Traits::Plain::Ptr<T> {};

template <typename T>
struct Ptr<T[]> : LWF::Traits::Plain::Ptr<T, T[]> {};

}}}} // namespace CShift::LWF::Traits::Subscriptable

#endif // CSHIFT_LWF_TRAITS_SUBSCRIPTABLE_PTR_H
