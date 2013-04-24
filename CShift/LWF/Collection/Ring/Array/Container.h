#ifndef CSHIFT_LWF_COLLECTION_RING_ARRAY_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_RING_ARRAY_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Dynamic/Array/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Ring {
namespace Array {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef typename Base::Allocator  Allocator;

  Void ensureCapacity(UInt capacity) {
    Base::ensureCapacity(capacity);
  }
  Void setCapacity(UInt capacity) {
    Base::setCapacity(capacity);
  }
  Void shrinkToFit() { setCapacity(0); }

  Container(const Allocator &allocator) : Base(allocator) {}
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Traits_>
struct Container
  : LWF::Collection::Dynamic::Array::Traits::Container<Traits_>
{
  private: typedef
    LWF::Collection::Dynamic::Array::Traits::Container<Traits_> Base;

  public: UInt capacity() const {
    const typename Base::Reversible &r = *this;
    return (r.end() - r.begin()) -  (Base::last() - Base::first());
  }

  ConstructionTransparency(Container, Base) {}

  protected: struct Capacity {
    UInt size() const { return size_; }
    Capacity(const Container &container) : size_(container.capacity()) {}
    private: UInt size_;
  };
#if 0 // Don't use the ring behaviour optimization here. TODO: move it to the range.fill/copy/etc().
  public: struct Split {

    struct Traits {
      template <typename Iterator>
      struct Range : LWF::Range<Iterator> {
        typedef LWF::Range<Iterator> Base;

        Range(const Iterator &begin, const Iterator &end)
          : Base(begin, end), break_(null, null) {}

        Bool continuous() const { return break_.empty(); }
        Base first () const { return Base(Base::begin(), break_.end()); }
        Base second() const { return Base(break_.begin(), Base::end()); }

        protected: Base &Break() { return break_; }
        private: Base break_;
      };
    };

    template <typename Iterator, typename = Void>
    struct Range {};

    template <typename U>
    struct Range<typename Container::Iterator, U>
      : Split::Traits::template Range<typename Container::Base::Reversible::Iterator> {
      typedef typename Split::Traits::template Range<
              typename Container::Base::Reversible::Iterator> Base;

      Range(const typename Container::Iterator &begin,
            const typename Container::Iterator &end) : Base(begin, end)  {
        if (!(Base::begin() < Base::end())) {
          Base::Break() = begin.range();
        }
      }
    };

    template <typename U>
    struct Range<typename Container::Reverse::Iterator, U>
      : Split::Traits::template Range<LWF::Reverse::Ptr<
            typename Container::Base::Reversible::Iterator> > {
      typedef typename Split::Traits::template Range<LWF::Reverse::Ptr<
              typename Container::Base::Reversible::Iterator> > Base;

      Range(const typename Container::Reverse::Iterator &begin,
            const typename Container::Reverse::Iterator &end)
        : Base(typename Container::Iterator(begin),
               typename Container::Iterator(end)) {

        if (!(Base::begin() < Base::end())) {
          LWF::Range<typename Container::Base::Reversible::Iterator>
                  range = typename Container::Iterator(begin).range();
          Base::Break() = LWF::Reverse::range(range);
        }
      }
    };

    template <typename Iterator>
    static Range<Iterator> range(const Iterator &begin, const Iterator &end) {
      return Range<Iterator>(begin, end);
    }
  };

  struct Traits {
    template <typename Iterator,
              Bool = LWF::Type<typename Iterator::Type>::Is::fundamental,
              typename U = Void>
    struct Tail : Container::Base::Traits::template Tail<Iterator> {};

    template <typename Iterator, typename U>
    struct Tail<Iterator, True, U> :
        Container::Base::Traits::template Tail<Iterator> {

      template <typename RangeIterator>
      static Void insert(Iterator &tail,
                         RangeIterator first, const RangeIterator &last) {
        UInt count = (last - first); if (0 == count) return;
        Iterator head = tail + count;
        typename Split::template Range<Iterator> range(tail, head);

        if (range.continuous()) {
          range.fill(first);
        } else {
          range.first().fill(first);
          range.second().fill(first + range.first().size());
        }
        tail = head;
      }
    };
  };

  protected: template <typename Iterator,
                       typename Base = typename Base::template Tail<Iterator,
                                typename Traits::template Tail<Iterator> > >
  struct Tail : Base { Tail(Iterator &tail) : Base(tail) {} };

  protected: template <typename Iterator> static
  Tail<Iterator> tail(Iterator &end) { return Tail<Iterator>(end); }
#endif
};

}} // namespace Low::Traits

}}}}} // namespace CShift::LWF::Collection::Ring::Array

#endif // CSHIFT_LWF_COLLECTION_RING_ARRAY_CONTAINER_H
