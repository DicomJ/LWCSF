#ifndef CSHIFT_LWF_COLLECTION_DYNAMIC_ARRAY_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_DYNAMIC_ARRAY_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Range.h"
#include "LWF/Reverse/range.h"
#include "LWF/Index/range.h"
#include "LWF/Value/Ptr.h"
#include "LWF/Value/Move/Ptr.h"

namespace CShift {
namespace LWF {
namespace Collection {
namespace Dynamic {
namespace Array {

namespace Tail {
namespace Traits {

template <typename Base>
struct Container : Base {

  protected: struct Traits {

    template <typename Iterator,
              typename = typename LWF::Type<typename Iterator::Type>::Kind>
    struct Tail {
      template <typename RangeIterator>
      static Void insert(Iterator &tail,
                         RangeIterator first, const RangeIterator &last) {
        UInt count = last - first;
        LWF::range(tail, count).fill(first);
        tail += count;
      }
      static Void erase(Iterator &tail, const Iterator &begin) {
        while (tail != begin) { tail = begin; }
      }
    };

    template <typename Iterator>
    struct Tail<Iterator, LWF::Kind::Nonfundamental> {
      template <typename RangeIterator>
      static Void insert(Iterator &tail,
                         RangeIterator first, const RangeIterator &last) {
        for (;first != last; ++tail, ++first) { *LWF::Move::ptr(tail) = *first; }
      }
      static Void erase(Iterator &tail, const Iterator &begin) {
        while (tail != begin) { *LWF::Move::ptr(--tail) = null; }
      }
    };
  };

  protected: template <typename Iterator,
                       typename Traits = typename Traits::template Tail<Iterator> >
  struct Tail {

    Tail(Iterator &tail_) : tail(tail_) {}

    template <typename RangeIterator>
    Tail &insert(RangeIterator first, const RangeIterator &last) {
      return Traits::insert(tail, first, last), *this;
    }
    template <typename RangeIterator>
    Tail &insert(const RangeIterator &first, UInt count) {
      return insert(first + 0, first + count);
    }
    Void erase(const Iterator &begin) {
      Traits::erase(tail, begin);
    }
    Void erase(UInt count) { return erase(tail - count); }

    private: Iterator &tail;
  };
  template <typename Iterator> static
  Tail<Iterator> tail(Iterator &end) { return Tail<Iterator>(end); }

  protected: ConstructionTransparency(Container, Base) {}
};

}} // namespasce Tail::Tratis

namespace Traits {

template <typename Traits>
struct Container
    : LWF::Collection::Dynamic::Array::Tail::Traits::Container<Traits>
{
  private: typedef
    LWF::Collection::Dynamic::Array::Tail::Traits::Container<Traits> Base;
  public : typedef typename Base::Allocator Allocator;
  public : typedef typename Base::Iterator  Iterator;

  struct Reverse { typedef LWF::Reverse::Ptr<Container::Iterator> Iterator; };

  Iterator                    first() const { return array.first; }
  Iterator                    last () const { return array.last ; }
  typename Reverse::Iterator &first()       { return array.first; }
  Iterator                   &last ()       { return array.last ; }

  private: struct Array {
    Array() {}
    Array(const Iterator &iterator) : first(iterator), last(iterator) {}
    typename Reverse::Iterator first; Iterator last;
  } array;

  protected: Container(UInt size, const Allocator &allocator)
    : Base(size, allocator), array(static_cast<const Base &>(*this).begin()) {}
  protected: Container(const Allocator &allocator)
    : Base(allocator), array(static_cast<const Base &>(*this).begin()) {}

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  protected: Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)) {
    LWF::swap(first(), container.first());
    LWF::swap(last (), container.last ());
  }

  protected: Container &operator = (Container &&container) {
    Base::operator = (LWF::Forward::reference<Base>(container));
    LWF::swap(first(), container.first());
    LWF::swap(last (), container.last ());
    return *this;
  }
  #endif // C++11

  public: Void swap(Container &container) {
    LWF::swap<Base>(*this, container);
    LWF::swap(first(), container.first());
    LWF::swap(last (), container.last ());
  }
};

} // namespace Traits

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef typename Base::Type       Type;
  typedef typename Base::Allocator  Allocator;
  typedef typename Base::Iterator   Iterator;

  Iterator begin() const { return Base::first(); }
  Iterator end  () const { return Base::last(); }

  UInt maxSize() const { return Base::allocator().maxSize();  }
  UInt      capacity() const { return typename Base::Capacity(*this).size(); }

  Void swap(const Iterator &one, const Iterator &other) {
    LWF::swap<Type>(*one, *other);
  }
  Void swap(Container &container) {
    if (this != &container) {
      Base::swap(container);
    }
  }

  Iterator erase(const Iterator &iterator) {
    return Base::erase(iterator, iterator + 1);
  }
  Iterator erase(const Iterator &first, const Iterator &last) {
    return Base::erase(first, last);
  }

#if PLATFORM_COMPILER_RVALUE_REFERENCE
  Iterator insert(const Iterator &position, Type &&value) {
    typedef typename LWF::Value<Type>::Move::template Ptr<Int> Ptr;
    return Base::insert(position, Ptr(&value), Ptr(&value, 1));
  }
#endif // C++11

  Iterator insert(const Iterator &position, Type &value) {
    typedef typename LWF::Value<Type>::template Ptr<Int> Ptr;
    return Base::insert(position, Ptr(&value), Ptr(&value, 1));
  }

  Iterator insert(const Iterator &position, const Type &value) {
    typedef typename LWF::Value<const Type>::template Ptr<Int> Ptr;
    return Base::insert(position, Ptr(&value), Ptr(&value, 1));
  }

  template <typename RangeIterator>
  Iterator insert (const Iterator &position,
                   const RangeIterator &first, const RangeIterator &last) {
    return Base::insert(position, first, last);
  }

  Void resize(UInt size, const Type &value = Type()) {
    Int difference = size - (end() - begin());
    if (difference > 0) {
      typedef typename LWF::Value<const Type>::template Ptr<Int> Ptr;
      Base::insert(end(), Ptr(&value), Ptr(&value, difference));
    } else {
      erase(end() + difference, end());
    }
  }

  Container(const Allocator &allocator) : Base(allocator) {}

  private: Void first() const;
  private: Void last () const;
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Base>
struct Container : Base {

  protected: template <typename T> struct Is;
  public : typedef typename Base::Iterator   Iterator;

  protected: template <typename TailIterator>
  Void erase(const Iterator &head, TailIterator &tail, UInt count) {
    TailIterator begin = head;
    LWF::range(begin + 0, tail - count).fill(begin + count);
    Container::tail(tail).erase(count);
  }

  protected: template <typename RangeIterator>
  Iterator insertFront(const Iterator &position,
                       const RangeIterator &first, const RangeIterator &last) {
    insert(position, Base::first(), LWF::Reverse::ptr(last), LWF::Reverse::ptr(first));
    return position;
  }

  protected: template <typename RangeIterator>
  Iterator insertBack (const Iterator &position,
                       const RangeIterator &first, const RangeIterator &last) {
    const UInt count = last - first;
    insert(position, Base::last(), first, last);
    return position + count;
  }

  protected: template <typename PositionIterator>
  Bool contains(const PositionIterator &iterator) const {
    return contains_(LWF::Reverse::reducted(iterator));
  }
  private: template <typename PositionIterator>
  Bool contains_(const PositionIterator &iterator,
                 typename LWF::Traits::Prediction<LWF::Reverse::Is<PositionIterator>::reverse>::Type * = 0) const {
    return LWF::Reverse::range(Base::first(), Base::last()).contains(Iterator(iterator));
  }
  private: template <typename PositionIterator>
  Bool contains_(const PositionIterator &iterator,
                 typename LWF::Traits::Prediction<!LWF::Reverse::Is<PositionIterator>::reverse>::Type * = 0) const {
    return LWF::range(Base::first(), Base::last()).contains(iterator);
  }

  private: template <typename TailIterator, typename RangeIterator>
  Void insert(const Iterator &head,TailIterator &tail,
              RangeIterator first, RangeIterator last) {
    TailIterator begin = head, end = tail;
    UInt count = last - first, size = end - begin;

    if (count > size) {
      Container::tail(tail).insert(first + size, count - size); count = size;
      Container::tail(tail).insert(begin, end);
    } else {
      Container::tail(tail).insert(end - count, end + 0);
      LWF::Reverse::range(begin + count, end + 0).fill(LWF::Reverse::ptr(end) + count);
    }

    if (1 == count) { *begin = *first; } else { insert(begin, first, count); }
  }

  private: template <typename TailIterator, typename RangeIterator>
  Void insert(const TailIterator &begin,
              const RangeIterator &first, Int count,
              typename LWF::Traits::Prediction<!Is<RangeIterator>::Iterator>::Type * = 0) {
    LWF::range(begin, count).fill(first);
  }

  private: template <typename TailIterator, typename RangeIterator>
  Void insert(const TailIterator &begin,
              const RangeIterator &first, UInt count,
              typename LWF::Traits::Prediction<Is<RangeIterator>::Iterator>::Type * = 0) {

    if (!this->contains(first)) {
      LWF::range(begin, count).fill(first);
    } else {
      TailIterator end = begin + count;
      RangeIterator last = first + count;
      LWF::Range<TailIterator> destination(begin, end);
      struct { TailIterator begin, end; } source = { Iterator(first), Iterator(last) };
      if (LWF::Reverse::Is<typename LWF::Reverse::Reducted<TailIterator>::Type>::reverse !=
          LWF::Reverse::Is<typename LWF::Reverse::Reducted<RangeIterator>::Type>::reverse) {
      //if (source.begin > source.end) { // Considered as reverse
        if (begin < source.end) {
          destination.fill(RangeIterator(Iterator(source.begin + count)));
        } else if (begin < source.begin) {
          LWF::Reverse::range(source.begin, end).fill(Reverse::ptr(last));
          LWF::range(begin, source.begin).reverse();
        } else {
          destination.fill(first);
        }
      } else { // forward
        if (begin <= source.begin) {
          destination.fill(RangeIterator(Iterator(source.begin + count)));
        } else if (begin < source.end) {
          LWF::Reverse::range(destination).fill(LWF::Reverse::ptr(last));
        } else {
          destination.fill(first);
        }
      }
    }
  }

  public: ConstructionTransparency(Container, Base) {}

  protected: struct Distance {
    UInt front, back;
    UInt size() const { return front + back; }
    Distance(const Container &container, const Iterator &position)
     : front(position - container.first()), back(container.last() - position) {}
  };
  struct Shift { UInt front, back;
    Shift(const Container &container, const Iterator &first, const Iterator &last)
      : front(first - container.first()), back(container.last() - last) {}
  };
};

template <typename Base>
template <typename T>
struct Container<Base>::Is {
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Iterator>::type;
};

}} // namespace Low::Traits

}}}}} // namespace CShift::LWF::Collection::Dynamic::Array

#endif // CSHIFT_LWF_COLLECTION_DYNAMIC_ARRAY_CONTAINER_H
