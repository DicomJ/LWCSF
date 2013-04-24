#ifndef CSHIFT_LWF_COLLECTION_REVERSIBLE_ARRAY_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_REVERSIBLE_ARRAY_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Dynamic/Array/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Array {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef typename Base::Allocator  Allocator;

  Void ensureCapacity(UInt front, UInt back) {
    Base::ensureCapacity(front, back);
  }
  Void ensureFrontCapacity(UInt front) {
    Base::ensureCapacity(front, Base::backCapacity());
  }
  Void ensureBackCapacity(UInt back) {
    Base::ensureCapacity(Base::frontCapacity(), back);
  }
  Void setCapacity(UInt front, UInt back) {
    Base::setCapacity(front, back);
  }
  Void setFrontCapacity(UInt front) {
        Base::setCapacity(front, Base::backCapacity());
  }
  Void setBackCapacity(UInt back) {
    Base::setCapacity(Base::frontCapacity(), back);
  }
  Void shrinkToFit() { setCapacity(0, 0); }

  Container(const Allocator &allocator) : Base(allocator) {}
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Traits>
struct Container
  : LWF::Collection::Dynamic::Array::Traits::Container<Traits>
{
  private: typedef
    LWF::Collection::Dynamic::Array::Traits::Container<Traits> Base;
  public:

  UInt frontCapacity() const { return Base::first() - Base::begin(); }
  UInt  backCapacity() const { return Base::end() - Base::last();    }

  ConstructionTransparency(Container, Base) {}

  protected: struct Capacity {
    UInt front, back;
    UInt size() const { return front + back; }
    Capacity(const Container &container) : front(container.frontCapacity()),
                                         back (container. backCapacity()) {}
    Capacity(UInt front_, UInt back_) : front(front_), back(back_) {}
  };
};

}} // namespace Low::Traits

}}}}} // namespace CShift::LWF::Collection::Reversible::Array

#endif // CSHIFT_LWF_COLLECTION_REVERSIBLE_ARRAY_CONTAINER_H
