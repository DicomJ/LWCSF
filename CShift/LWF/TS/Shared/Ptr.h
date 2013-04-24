#ifndef CSHIFT_LWF_TS_SHARED_PTR_H
#define CSHIFT_LWF_TS_SHARED_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Shared/Ptr.h"
#include "LWF/TS/Shared/Counter.h"


namespace CShift {
namespace LWF {
namespace TS {
namespace Shared {

template <typename Traits,
          typename Deleter = LWF::Unique::Deleter<Traits>,
          typename DynamicAllocator = LWF::Shared::Counter::Allocator<LWF::TS::Shared::Counter> >
struct Ptr
  : LWF::Shared::Ptr<Traits, Deleter,
                     LWF::TS::Shared::Counter, DynamicAllocator>
{
  private: typedef
    LWF::Shared::Ptr<Traits, Deleter,
                     LWF::TS::Shared::Counter, DynamicAllocator> Base;
  public: typedef
    typename Base::Type Type;

  Ptr(Type *ptr,
      const Deleter &deleter = Deleter(),
      const DynamicAllocator &dynamicAllocator = DynamicAllocator())
    : Base(ptr, deleter, dynamicAllocator) {}

  Ptr(const Null &ptr = null,
      const Deleter &deleter = Deleter(),
      const DynamicAllocator &dynamicAllocator = DynamicAllocator())
    : Base(ptr, deleter, dynamicAllocator) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U, typename D, typename CA>
  Ptr(const Ptr<U, D, CA> &ptr) : Base(ptr) {}

  template <typename U, typename D, typename CA>
  Ptr &operator = (const Ptr<U, D, CA> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }
};

}}}} // namespace CShift::LWF::TS::Shared

#endif // CSHIFT_LWF_TS_SHARED_PTR_H
