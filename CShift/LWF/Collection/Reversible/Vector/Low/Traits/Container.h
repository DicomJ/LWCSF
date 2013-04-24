#ifndef CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_LOW_TRAITS_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_LOW_TRAITS_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Unique/Array.h"
#include "LWF/Deallocation/Deleter.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Vector {

namespace Low {
namespace Traits {

template <typename Type_, typename Allocator_ >
struct Container
  : LWF::Unique::Array<Type_, LWF::Deallocation::Deleter<Allocator_> > {
  private: typedef
    LWF::Unique::Array<Type_, LWF::Deallocation::Deleter<Allocator_> > Base;
  public:

  typedef Allocator_ Allocator;

  public:       Allocator &allocator()       { return Base::owner(); }
  public: const Allocator &allocator() const { return Base::owner(); }

  protected: Container(UInt size, const Allocator &allocator)
    : Base(allocator.allocate(size), size, allocator) {
  }

  protected: Container(const Allocator &allocator) : Base(allocator) {}

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  protected: Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)) {
  }

  protected: Container &operator = (Container &&container) {
    Base::operator = (LWF::Forward::reference<Base>(container));
    return *this;
  }
  #endif // C++11

  public: Void swap(Container &container) {
    LWF::swap<Base>(*this, container);
  }

  protected: template <typename Base>
  struct Swapper : Base {
    ConstructionTransparency(Swapper, Base) {}
    ~Swapper() {
      const Base &base = *this;
      Base::erase(base.first(), base.last());
    }
  };
};

}}}}}}} // namespace CShift::LWF::Collection::Reversible::Vector::Low::Traits

#endif // CSHIFT_LWF_COLLECTION_REVERSIBLE_VECTOR_LOW_TRAITS_CONTAINER_H
