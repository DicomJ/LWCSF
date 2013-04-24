#ifndef CSHIFT_LWF_COLLECTION_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/swap.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Traits {

template <typename Type_, typename Allocator_>
struct Container : private Allocator_ {

  typedef Allocator_ Allocator;
  typedef Type_ Type;

  Void swap(Container &container) { LWF::swap<Allocator>(*this, container); }

  Allocator &allocator() { return *this; }
  const Allocator &allocator() const { return *this; }

  Container(const Allocator &allocator) : Allocator(allocator) {}
};

}}}} // namespace CShift::LWF::Collection::Traits

#endif // CSHIFT_LWF_COLLECTION_CONTAINER_H 
