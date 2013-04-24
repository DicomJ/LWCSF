#ifndef CSHIFT_LWF_COW_H
#define CSHIFT_LWF_COW_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"  
#include "LWF/Collection/Dynamic/Container.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Shared/Ptr.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace COW {

template <typename Base>
struct Allocator : Base { struct COW {

  typedef Allocator COWAllocator;

  struct Traits {
    template <typename Traits>
    struct Allocator : LWF::Unique::Allocator<Traits> {
      Allocator(const COWAllocator &) {}
    };
  };

  struct Dynamic {
    typedef UInt Counter;
    struct Allocator : LWF::Unique::Allocator<Counter> {
      Allocator(const COWAllocator &) {}
    };
  };

};};

}}}} // namespace CShift::LWF::Collection::COW



namespace CShift {
namespace LWF {
namespace Collection {
namespace COW {
namespace Traits {

template <typename Traits>
struct Ptr
  : LWF::Shared::Ptr<Traits,
                     typename Traits::Allocator::COW::Traits::template Allocator<Traits>,
                     typename Traits::Allocator::COW::Dynamic::Counter,
                     typename Traits::Allocator::COW::Dynamic::Allocator>
{
  public: typedef typename Traits::Allocator Allocator;
  private: typedef
    LWF::Shared::Ptr<Traits,
                      typename Allocator::COW::Traits::template Allocator<Traits>,
                      typename Allocator::COW::Dynamic::Counter,
                      typename Allocator::COW::Dynamic::Allocator> Base;
  public:

  Ptr(const Allocator &allocator) : Base(Ptr::traits(allocator), allocator, allocator) {}
  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr)  { Base::operator = (ptr); return *this; }

  const Traits &operator * () const { return Base::operator * (); }
  Traits & operator * () {
    if (!Base::unique()) {
      Traits &traits = Base::operator * ();
      Allocator &allocator = traits.allocator();
      Base::operator = (Base(Ptr::traits(traits, allocator), allocator, allocator));
    }
    return Base::operator * ();
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Ptr(Ptr &&ptr) : Base(ptr) { }
  Ptr &operator = (Ptr &&ptr) { Base::swap(ptr); return *this; }
  #endif // C++11

  private: typedef typename Allocator::COW::Traits::template Allocator<Traits> TraitsAllocator;

  private: static Traits *traits(const Allocator &cowAllocator) {
    TraitsAllocator allocator(cowAllocator);
    return new (allocator) Traits(cowAllocator);
  }
  private: static Traits *traits(const Traits &traits, const Allocator &cowAllocator) {
    TraitsAllocator allocator(cowAllocator);
    return new (allocator) Traits(traits, cowAllocator);
  }
};

template <typename Traits>
class Container : LWF::Collection::COW::Traits::Ptr<Traits> {
  typedef LWF::Collection::COW::Traits::Ptr<Traits> Base; public:

  typedef typename Base::Type::Type       Type;
  typedef typename Base::Type::Iterator   Iterator;
  typedef typename Base::Type::Allocator  Allocator;

  Iterator begin()       { return (**this).begin(); }
  Iterator end  ()       { return (**this).end  (); }
  Iterator begin() const { return (**this).begin(); }
  Iterator end  () const { return (**this).end  (); }

  UInt maxSize () const { return (**this).maxSize(); }
  UInt capacity() const { return (**this).capacity(); }

  UInt frontCapacity() const { return (**this).frontCapacity(); }
  UInt  backCapacity() const { return (**this). backCapacity(); }

  Void ensureCapacity(UInt capacity) {
    (**this).ensureCapacity(capacity);
  }
  Void ensureCapacity(UInt front, UInt back) {
    (**this).ensureCapacity(front, back);
  }
  Void ensureFrontCapacity(UInt front) {
    (**this).ensureFrontCapacity(front);
  }
  Void ensureBackCapacity (UInt back ) {
    (**this).ensureBackCapacity (back );
  }
  Void setCapacity(UInt capacity) {
    (**this).setCapacity(capacity);
  }
  Void setCapacity(UInt front, UInt back) {
    (**this).setCapacity(front, back);
  }
  Void setFrontCapacity(UInt front) {
    (**this).setFrontCapacity(front);
  }
  Void setBackCapacity(UInt back) {
    (**this).setBackCapacity(back);
  }
  Void shrinkToFit() { (**this).shrinkToFit(); }

  Void swap(const Iterator &one, const Iterator &other) {
    (**this).swap(one, other);
  }
  Void swap(Container &container) {
    (**this).swap(*container);
  }

  Iterator erase(const Iterator &iterator) {
    return (**this).erase(iterator);
  }
  Iterator erase(const Iterator &first, const Iterator &last) {
    return (**this).erase(first, last);
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Iterator insert(const Iterator &position, Type &&value) {
    return (**this).insert(position, LWF::Forward::reference<Type>(value));
  }
  #endif // C++11
  Iterator insert(const Iterator &position, Type &value) {
    return (**this).insert(position, value);
  }
  Iterator insert(const Iterator &position, const Type &value) {
    return (**this).insert(position, value);
  }
  template <typename RangeIterator>
  Iterator insert (const Iterator &position,
                   const RangeIterator &first, const RangeIterator &last) {
    return (**this).insert(position, first, last);
  }

  Void resize(UInt size, const Type &value = Type()) {
    return (**this).resize(size, value);
  }

  Container(const Allocator &allocator) : Base(allocator) {}
  Container(const Container &container) : Base(container) {}
  Container &operator = (const Container &container)  {
    Base::operator = (container); return *this;
  }
};

}}}}} // namespace CShift::LWF::Collection::COW::Traits



namespace CShift {
namespace LWF {

template <typename Traits>
struct COW
  : LWF::Collection::Dynamic::    Container<
    LWF::Collection::Static::     Container<
    LWF::Collection::COW::Traits::Container<Traits> > >
{
  private: typedef
    LWF::Collection::Dynamic::    Container<
                    LWF::Collection::Static::     Container<
                    LWF::Collection::COW::Traits::Container<Traits> > > Base;
  public:

  typedef typename Base::Type      Type;
  typedef typename Base::Allocator Allocator;

  COW(const Allocator &allocator = Allocator()) : Base(allocator) {}

  COW(UInt count, const Type &value = Type(),
      const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  COW(const Iterator &first, const Iterator &last,
      const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  COW(const Range &range, const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  COW &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  COW(const LWF::Initializer::List<Type> &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  COW &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  COW (const COW &cow, const Allocator &allocator)
    : Base(cow, allocator) {} // Makes a copy

  COW (const COW &cow)
    : Base(static_cast<const Base &>(cow)) {} // inherits

  COW &operator = (const COW &cow) {
    Base::operator = (static_cast<const Base &>(cow));
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  COW(COW &&cow) : Base(LWF::Forward::reference<Base>(cow)) {}

  COW &operator = (COW &&cow) {
    Base::operator = (LWF::Forward::reference<Base>(cow));
    return *this;
  }
  #endif // C++11
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_COW_H
