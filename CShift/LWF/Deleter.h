#ifndef CSHIFT_LWF_DELETER_H
#define CSHIFT_LWF_DELETER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Traits/Subscriptable/Ptr.h"


namespace CShift {
namespace LWF {

template <typename T>
struct Deleter      : LWF::Traits::Subscriptable::Ptr<T  >
{ Void Delete (T *ptr) const { delete    ptr; } };
template <typename T>
struct Deleter<T[]> : LWF::Traits::Subscriptable::Ptr<T[]>
{ Void Delete (T *ptr) const { delete [] ptr; } };

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_DELETER_H
