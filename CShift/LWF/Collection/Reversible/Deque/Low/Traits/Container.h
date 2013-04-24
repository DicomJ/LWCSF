#ifndef CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_LOW_TRAITS_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_LOW_TRAITS_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Vector.h"
#include "LWF/Static/Unique/Array.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Reversible {
namespace Deque {
namespace Low {
namespace Traits {

template <typename Base>
struct Container : Base {

  public:  typedef typename Base::Allocator Allocator;
  public:  struct Block;
  protected: typedef LWF::Vector<Block, typename Allocator::Rebind::
                                               template With<Block> > Map;
  public:  struct Iterator;

  Iterator begin() const { return at(typename Iterator::Index(         0, 0)); }
  Iterator end  () const { return at(typename Iterator::Index(map.size(), 0)); }
  typename Map::Reverse::Iterator  mbegin() { return map.rend  (); }
  typename Map::         Iterator  mend  () { return map. end  (); }
  typename Map::Reverse::Iterator mrbegin() { return map.rbegin(); }
  typename Map::         Iterator mrend  () { return map. begin(); }
  static typename Map::Iterator
  mpos (const typename Map::Iterator &pos)  { return pos;          }
  static typename Map::Reverse::Iterator
  mrpos(const typename Map::Iterator &pos)  { return pos;          }

  protected: Container(const Allocator &allocator)
    : Base(allocator), map(typename Map::Allocator(allocator)) {
  }

  protected: Iterator at(const typename Iterator::Index &index) const {
    return Iterator(LWF::range(map), index);
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  protected: Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)),
      map(LWF::Move::reference(container.map)) {
  }

  protected: Container &operator = (Container &&container) {
    Base::operator = (LWF::Forward::reference<Base>(container));
    LWF::swap(map, container.map);
    return *this;
  }
  #endif // C++11

  public: Void swap(Container &container) {
    LWF::swap<Base>(*this, container);
    LWF::swap<Map>(map, container.map);
  }

  protected: Map map;
};

template <typename CBase>
struct Container<CBase>::Iterator : Container::Block::Iterator {
  private: typedef typename Container::Block::Iterator Base; public:

  Iterator(const LWF::Range<typename Container::Map::Iterator> &base,
           const typename Base::Index &index) : Base(base, index){}

  Iterator(const Null & = null) : Base(null) {}
  Iterator &operator = (const Null &) { Base::operator = (null); return *this; }

  Iterator(const Iterator &iterator) : Base(iterator) {}
  Iterator &operator = (const Iterator &iterator) {
    Base::operator = (iterator); return *this;
  }

  WeaknessTransparency(Iterator, Base) {}
};

template <typename CBase>
struct Container<CBase>::Block :
    LWF::Static::Unique::Array<typename Container::Type,
                               Container::Allocator::Block::size,
                               LWF::Deallocation::Deleter<typename Container::Allocator> > {
  static const UInt size = Container::Allocator::Block::size;
  typedef LWF::Static::Unique::Array<
                               typename Container::Type,
                               Block::size,
                               LWF::Deallocation::Deleter<typename Container::Allocator> > Base;

  protected: struct Traits { struct Iterator;  }; public:
  typedef LWF::Ptr<typename Traits::Iterator> Iterator;

  struct Enlarge {
    struct Spread : private Iterator::Index {
      Spread(UInt count) : Iterator::Index(count) {}
      UInt size() const {
        return this->block + (this->offset % Block::size != 0 ? 1 : 0);
      }
    };
  };
  struct Shrink {
    struct Spread : private Iterator::Index {
      Spread(UInt count) : Iterator::Index(count) {}
      UInt size() const { return this->block; }
    };
  };

  Block(Allocator &allocator) : Base(allocator.allocate(size), allocator) {}
};

template <typename CBase>
struct Container<CBase>::Block::Traits::Iterator : Block::Base::Iterator
{
  typedef typename Block::Base::Iterator Base;
  struct Index;

  Iterator operator + (Int index) const {
    return Iterator(range, this->index() += index);
  }

  Int operator - (const Iterator &iterator) const {
    return (this->range.begin() - iterator.range.begin()) * Block::size +
           (this->index() - iterator.index());
  }

  typename Base::Return::Type operator [] (Int index) const {
    return *(*this + index);
  }

  Index index() const {
    return Index(range.index(), Base::operator - (range.block()) );
  }

  Iterator(const Null & = null) : Base(null), range(null) {}
  Iterator &operator = (const Null &) {
    Base::operator = (null); range = null;
    return *this;
  }

  protected: struct Range;

  public: typename Range::Iterator block() const { return range.map(); }

  protected: Iterator(const typename Range::Base &base, const Index &index)
    : range(base, index.block) {
    Base::operator = (range.block() + index.offset);
  }

  protected: Range range;
};

template <typename CBase>
struct Container<CBase>::Block::Traits::Iterator::Range
  : LWF::Range<typename Map::Iterator> {

  typedef LWF::Range<typename Map::Iterator> Base;

  Range(const Base &base, Int index = 0) : Base(base) { block_ = Base::begin() + index; }

  Range(const Null & = null) : Base(null, null), block_(null) {}

  Range &operator = (const Null &) {
    Base::operator = (Base(null, null)); block_ = null; return *this;
  }

  Int index() const { return block_ - this->begin(); }

  typename Iterator::Base block() const {
    return this->contains(block_) ? block_->begin() : null;
  }

  typename Map::Iterator map() const { return block_; }

  private: typename Map::Iterator block_;
};

template <typename CBase>
struct Container<CBase>::Block::Traits::Iterator::Index {

  Int block, offset;

  Index(Int index) {
    #if 0
      // !!!The code Independent of the compiler's implementation
      // of the resulting sign of modulo operator with negative operand
      if (index < 0) {
        index = -index;
        block = index / Block::size; offset = index % Block::size;
        block = -block; offset = -offset;
        if (offset < 0) { block -= 1; offset += Block::size; }
      } else {
        block = index / Block::size; offset = index % Block::size;
      }
    #else
      block = index / Int(Block::size); offset = index % Int(Block::size);
      if (offset < 0) { block -= 1; offset += Block::size; }
    #endif
  }
  Index(Int block, Int offset) { this->block = block; this->offset = offset; }

  Int operator - (const Index &index) {
    return Block::size * (block - index.block) + (offset - index.offset);
  }

  Index &operator += (Int index_) {
    Index index(index_ + offset); block += index.block; offset = index.offset;
    return *this;
  }

  Index &operator += (const typename Container::Map::Reverse::Iterator &) {
    ++block; return *this;
  }
  Index &operator += (const typename Container::Map::Iterator &) {
    return *this;
  }
  Index &operator -= (const typename Container::Map::Reverse::Iterator &) {
    return *this;
  }
  Index &operator -= (const typename Container::Map::Iterator &) {
    --block; return *this;
  }
};

}}}}}}} // namespace CShift::LWF::Collection::Reversible::Deque::Low::Traits

#endif // CSHIFT_LWF_COLLECTION_REVERSIBLE_DEQUE_LOW_TRAITS_CONTAINER_H
