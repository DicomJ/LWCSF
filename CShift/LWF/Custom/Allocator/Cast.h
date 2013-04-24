#ifndef CSHIFT_LWF_CUSTOM_ALLOCATOR_CAST_H
#define CSHIFT_LWF_CUSTOM_ALLOCATOR_CAST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"


namespace CShift {
namespace LWF {
namespace Custom {
namespace Allocator {

template <typename T,
          Bool pointer = LWF::Type<typename LWF::Type<T>::
                         Kind>::Is::Equal::template To<LWF::Kind::Pointer>::type>
struct Cast;

}}}} // namespace CShift::LWF::Custom::Allocator


namespace CShift {
namespace LWF {
namespace Custom {
namespace Allocator {

template <typename T>
struct Cast <T, False > {
  static const T &   allocator(const T &allocator_  ) { return allocator_;   }
  static const T & deallocator(const T &deallocator_) { return deallocator_; }
  static       T &   allocator(      T &allocator_  ) { return allocator_;   }
  static       T & deallocator(      T &deallocator_) { return deallocator_; }
};

}}}} // namespace CShift::LWF::Custom::Allocator

#endif // CSHIFT_LWF_CUSTOM_ALLOCATOR_H
