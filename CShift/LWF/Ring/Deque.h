#ifndef CSHIFT_LWF_RING_DEQUE_H
#define CSHIFT_LWF_RING_DEQUE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/min.max.h"
#include "LWF/Collection/Ring/Array/Container.h"
#include "LWF/Collection/Reversible/Deque/Low/Traits/Container.h"
#include "LWF/Collection/Reversible/Deque/Allocator.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Ring {
namespace Deque {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {
  public:    typedef typename Base::Type      Type;
  public:    typedef typename Base::Allocator Allocator;
  public:    typedef typename Base::Iterator  Iterator;
  public:    typedef typename Base::Block     Block;
  protected: typedef typename Base::Capacity  Capacity;

  protected: Container(const Allocator &allocator) : Base(allocator) {}

  protected: Void ensureCapacity(UInt capacity_) {
    Capacity capacity(*this);
    Int difference = Int(capacity_ - capacity.size());
    if (difference > 0) { enlarge(difference); }
  }

  protected: Void setCapacity(UInt capacity_) {
    Capacity capacity(*this);
    Int difference = Int(capacity_ - capacity.size());
    if (difference > 0) {  enlarge(difference); }
    else if (difference < 0) { shrink(-difference); }
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    typename Base::Shift shift(*this, first, last); UInt count = last - first;
    return (shift.front < shift.back) ?
              (Base::erase(last , Base::first(), count), last) :
              (Base::erase(first, Base::last (), count), first) ;
  }

  protected: template <typename RangeIterator>
  Iterator insert(Iterator position, RangeIterator first, RangeIterator last) {
    const UInt count = last - first;
    if (0 == count) { return position; }

    Capacity capacity(*this);
    Int difference = Int(count - capacity.size());
    if (difference > 0) {
      enlarge(difference, position, first, last);
    }

    const typename Base::Distance distance(*this, position);
    return (distance.front < distance.back) ?
       Base::insertFront(position, first, last) :
       Base::insertBack(position, first, last);
  }

  private: Void enlarge(const typename Block::Enlarge::Spread &spread) {
    UInt count = spread.size();
    const Container &cthis = *this;
    const typename Base::Reversible::Iterator &first = cthis.first();
    const typename Base::Reversible::Iterator &last = cthis.last();
    if (cthis.first() == cthis.last() || first < last) {
        enlarge(Base::mend  (), count - count / 2);
        enlarge(Base::mbegin(),     0 + count / 2);
    } else {
      if (first.block() == last.block()) {
          Block &block = *first.block();
          UInt front = (const typename Block::Base::Iterator &)last - block.begin(),
               back  = block.end() - first;
          if (front != 0 && back != 0) {
            split(first.block(), front, back); --count;
          }
      }
      enlarge(Base::mbegin(), Base::mpos(cthis.first().block()), count);
    }
  }

  private: Void shrink(const typename Block::Shrink::Spread &spread) {
    UInt count = spread.size();
    const Container &cthis = *this;
    const typename Base::Reversible::Iterator &first = cthis.first();
    const typename Base::Reversible::Iterator &last = cthis.last();
    if (first <= last) {
      UInt front = typename Block::Shrink::Spread(first - Base::begin()).size();
      front = LWF::min(front, count);
      shrink(Base::mrend (),  front);
      shrink(Base::mrbegin(), count - front);
    } else {
      if (first.block() == last.block()) { --count; }
      shrink(Base::mend(), Base::mrpos(first.block()), count);
    }
  }

  template <typename Iterator>
  struct Splitter {
    struct Tailing : LWF::Collection::Dynamic::Array::Tail::Traits::
                     Container<typename Block::Base> {
       typedef typename Tailing::template Tail<Iterator> Tail;
    }; typedef typename Tailing::Tail Tail;

    Splitter(const Iterator &begin_) : end(begin_), begin(begin_) {}
    ~Splitter() { Tail(end).erase(begin); }

    Void insert(const Iterator &begin, UInt count) {
      Tail(end).insert(begin, count);
    }

    Void swap(const Iterator &begin, UInt count) {
      this->end = (this->begin = begin) + count;
    }
    private: Iterator end, begin;
  };

  private: Void split(const typename Container::Map::Iterator &block,
                      UInt front, UInt back) {
    const Container &cthis = *this;
    Block &oldBlock = *block, newBlock(Base::allocator());

    typename Container::Iterator::Index first = cthis.first().index(),
                                        last  = cthis.last ().index();
    if (front < back) {
      Splitter<typename Block::Base::Iterator> splitter(newBlock.begin());
      splitter.insert(oldBlock.begin(), front);
      Block &oldBlock = *Base::map.insert(block, newBlock);
      splitter.swap(oldBlock.begin(), front);

    } else {
      Splitter<typename Block::Base::Reverse::Iterator> splitter(newBlock.rbegin());
      splitter.insert(oldBlock.rbegin(), back);
      Block &oldBlock = *(Base::map.insert(block + 1, newBlock) - 2);
      splitter.swap(oldBlock.rbegin(), back);
    }
    this->first() = Base::at(first += Base::mbegin());
    this->last () = Base::at(last);
  }

  private: template <typename MapIterator>
  Void enlarge(MapIterator end, UInt count) { enlarge(end, end, count); }

  private: template <typename MapBeginIterator, typename MapEndIterator>
  Void enlarge(const MapBeginIterator &begin, MapEndIterator end, UInt count) {
    const Container &cthis = *this;
    for (typename Iterator::Index first = cthis.first().index(),
                                  last  = cthis.last ().index();
         count-- != 0;            this->first() = Base::at(first += begin),
                                  this->last () = Base::at(last  += end)) {
      Block block(Base::allocator());
      end = Base::map.insert(end, block);
    }
  }

  private: template <typename MapIterator>
  Void shrink(MapIterator end, UInt count) { shrink(end, end, count); }

  private: template <typename MapBeginIterator, typename MapEndIterator>
  Void shrink(const MapBeginIterator &begin, MapEndIterator end, UInt count) {
    const Container &cthis = *this;
    for (typename Iterator::Index first = cthis.first().index(),
                                  last  = cthis.last ().index();
         count-- != 0;            this->first() = Iterator(Base::at(first -= begin)),
                                  this->last () = Iterator(Base::at(last  -= end))) {
      end = Base::map.erase(end);
    }
  }

  private:  struct Index {
    Index(const Container &container, const Iterator &iterator) :
      index(iterator - container.first()) {}
    Iterator operator () (const Container &container) const {
      return container.first() + index;
    } private: UInt index;
  };

  private:  template <typename RangeIterator>
  Void enlarge(UInt count, Iterator &position,
               RangeIterator &first, RangeIterator &last,
               typename LWF::Traits::Prediction<Base::template Is<RangeIterator>::Iterator>::Type * = 0) {

      if (Base::contains(first)) {
        struct { Index first, last; } index = {
          Index(*this, first), Index(*this, last)
        }; enlarge(count, position);
        first = index.first(*this); last  = index.last(*this);
      } else {
        enlarge(count, position);
      }
  }
  private: Void enlarge(UInt count, Iterator &position) {
    Index index(*this, position); enlarge(count); position = index(*this);
  }
  private:  template <typename RangeIterator>
  Void enlarge(UInt count,  Iterator &position,
               const RangeIterator &/*first*/, const RangeIterator &/*last*/,
               typename LWF::Traits::Prediction<!Base::template Is<RangeIterator>::Iterator>::Type * = 0) {
     enlarge(count, position);
  }
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef Base Reversible;
  typedef typename Base::Allocator Allocator;
  protected: struct Traits { struct Iterator;  }; public:
  struct Iterator;
  Iterator begin() const { return Iterator(Base::begin(), 0); }
  Void end() const;

  protected: Iterator at(const typename Iterator::Index &index) const {
    return Iterator(Base::at(index), index);
  }

  Container(const Allocator &allocator) : Base(allocator) {}
};

template <typename CBase>
struct Container<CBase>::Traits::Iterator : CBase::Iterator {
  private: typedef typename CBase::Iterator Base;
  public: struct Index;

  Index index() const { return Index(Base::index(), absolute); }

  LWF::Range<Base> range() const { return LWF::Range<Base>(
          Base(Base::range, typename Base::Index(0, 0)),
          Base(Base::range, typename Base::Index(Base::range.size(), 0)));
  }

  Iterator operator + (Int offset) const {
    Index index(Base::index(), absolute);
    (index += offset) %= Base::range.size();
    return Iterator(Base(Base::range, index),
                    (const typename Index::Absolute&)index);
  }

  Bool operator == (const Iterator &iterator) const {
    return absolute == iterator.absolute;
  }

  Int operator - (const Iterator &iterator) const {
    return (this->index() - iterator.index()) +
        (Base::range.begin() - iterator.Base::range.begin()) * CBase::Block::size;
  }

  typename Base::Return::Type operator [] (Int index) const {
    return *(*this + index);
  }
  Iterator(const Base &base, const typename Index::Absolute &absolute_/* = 0*/)
    : Base(base), absolute(absolute_) {}
  Iterator(const Iterator &iterator)
    : Base(iterator), absolute(iterator.absolute) {}

  private: typename Index::Absolute absolute;
};

template <typename CBase>
struct Container<CBase>::Iterator : LWF::Ptr<typename Traits::Iterator> {
  private: typedef typename LWF::Ptr<typename Traits::Iterator> Base; public:

  Iterator(const typename CBase::Iterator &base,
           const typename Base::Index::Absolute &absolute)
    : Base(base, absolute) {}

  Iterator(const Null & = null) : Base(null, 0) {}
  Iterator &operator = (const Null &) { Base::operator = (null); return *this; }

  Iterator(const Iterator &iterator) : Base(iterator) {}
  Iterator &operator = (const Iterator &iterator) {
    Base::operator = (iterator); return *this;
  }

  Iterator(const Base &base) : Base(base) {}
  Iterator &operator = (const Base &base) {
    Base::operator = (base); return *this;
  }
  ExplictWeaknessTransparency(Iterator, Base) {}
};

template <typename CBase>
struct Container<CBase>::Traits::Iterator::Index
    : CBase::Iterator::Index {
  private: typedef typename CBase::Iterator::Index Base; public:
  typedef Int Absolute;

  Index(const Base &base, const Absolute &absolute_) : Base(base), absolute(absolute_) {}

  Int operator - (const Index &index) {
    return absolute - index.absolute;
  }

  Index &operator += (Int index) {
    absolute += index, Base::operator += (index); return *this;
  }

  Index &operator %= (UInt blocks) {
    Int &block = Base::block;
    if (blocks != 0) {
      #if 0
        if (block < 0) {
          block = -block; block %= blocks; block = -block;
          if (block < 0) { block += blocks; }
        } else {
          block %= blocks;
        }
      #else
        block %= Int(blocks);
        if (block < 0) { block += blocks; }
      #endif
    } return *this;
  }

  Index &operator += (const typename Container::Map::Reverse::Iterator &u) {
    Base::operator += (u); return *this;
  }
  Index &operator += (const typename Container::Map::Iterator &u) {
    Base::operator += (u); return *this;
  }
  Index &operator -= (const typename Container::Map::Reverse::Iterator &u) {
    Base::operator -= (u);  return *this;
  }
  Index &operator -= (const typename Container::Map::Iterator &u) {
    Base::operator -= (u); return *this;
  }

  operator const Absolute & () const { return absolute; }

  private: Absolute absolute;
};

}} // namespace Low::Traits

template <typename Type, UInt blockSize = 128>
struct Allocator : LWF::Collection::Reversible::Deque::Allocator<Type, blockSize> {};

}}}}} // namespace CShift::LWF::Collection::Ring::Deque


namespace CShift {
namespace LWF {
namespace Ring {

template <typename Type,
          typename Allocator = LWF::Collection::Ring::Deque::Allocator<Type> >
struct Deque
  : LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Ring      ::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::Ring      ::Deque::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::Ring      ::Array::Low ::Traits::Container<
    LWF::Collection::Ring      ::Deque::Low ::Traits::Container<
    LWF::Collection::Reversible::Deque::Low ::Traits::Container<
    LWF::Collection::Traits::Container<Type, Allocator> > > > > > > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Ring      ::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::Ring      ::Deque::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::Ring      ::Array::Low ::Traits::Container<
    LWF::Collection::Ring      ::Deque::Low ::Traits::Container<
    LWF::Collection::Reversible::Deque::Low ::Traits::Container<
    LWF::Collection::Traits::Container<Type, Allocator> > > > > > > > > > Base;
  public:

  Deque(const Allocator &allocator = Allocator()) : Base(allocator) {}

  Deque(UInt count, const Type &value = Type(),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  Deque(const Iterator &first, const Iterator &last, const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  Deque(const Range &range,
         const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  Deque &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Deque(const LWF::Initializer::List<Type> &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  Deque &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  Deque (const Deque &Deque,
          const Allocator &allocator = Allocator())
    : Base(Deque, allocator) {}

  Deque &operator = (const Deque &Deque) {
    Base::operator = (Deque);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Deque(Deque &&Deque) : Base(LWF::Forward::reference<Base>(Deque)) {}

  Deque &operator = (Deque &&Deque) {
    Base::operator = (LWF::Forward::reference<Base>(Deque));
    return *this;
  }
  #endif // C++11
};

}}} // namespace CShift::LWF::Ring

#endif // CSHIFT_LWF_RING_DEQUE_H
