#ifndef CSHIFT_LWF_SCO_H
#define CSHIFT_LWF_SCO_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Dynamic/Container.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Collection/Reversible/Array/Container.h"
#include "LWF/Collection/Container.h"
#include "LWF/Static/Weak/Array.h"
#include "LWF/Shortest/Integer.h"
#include "LWF/Traits/Surrogate.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace SCO { // Small(Short) Container Optimization

namespace Short {

namespace High {
namespace Traits {

template <typename Base>
struct Container : Base {

  typedef typename Base::Type       Type;
  typedef typename Base::Allocator  Allocator;
  typedef typename Base::Iterator   Iterator;

  protected: Container(const Allocator &allocator) : Base(allocator) {}

  protected: template <typename RangeIterator>
  Iterator insert(const Iterator &position,
                  const RangeIterator &first, const RangeIterator &last) {
    return Base::insertBack(position, first, last);
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    Base::erase(first, Base::last(), last - first); return first;
  }
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename Traits>
struct Container
  : LWF::Collection::Dynamic::Array::Tail::Traits::Container<Traits>
{
  private: typedef
    LWF::Collection::Dynamic::Array::Tail::Traits::Container<Traits> Base;
  public: typedef typename Base::Iterator Iterator;
  public: typedef LWF::Range<Iterator>    Allocator;
  public: typedef typename Base::Type     Type;

  protected: Iterator  first() const { return Base::begin(); }
  protected: Iterator  last () const { return last_; }
  protected: Iterator &last ()       { return last_; }

  Container(const Allocator &allocator)
    : Base (allocator.begin()), last_(allocator.end()) {}

  protected: Void detach() {
    static_cast<Traits &>(*this) = last() = null;
  }

  private: Iterator last_;
};

}} // namespace Low::Traits

template <typename Type, UInt size>
struct Container
  : LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::SCO::Short::       High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::SCO::Short::       Low ::Traits::Container<
           LWF::Static::Weak::Array<Type, size> > > > > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::SCO::Short::       High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::Low ::Traits::Container<
    LWF::Collection::SCO::Short::       Low ::Traits::Container<
           LWF::Static::Weak::Array<Type, size> > > > > > > > Base;
  public:

  typedef typename Base::Iterator   Iterator;
  typedef typename Base::Allocator  Allocator;

  static const UInt maxSize = size;

  UInt frontCapacity() const { return backCapacity();         }
  UInt  backCapacity() const { return maxSize - Base::size(); }

  Container(const Iterator &begin, UInt count) : Base(Allocator(begin, count)) {}
  ~Container() { Base::detach(); }
};

} // namespace Short

namespace Traits {

template <typename Short, typename Long>
struct Container : LWF::Collection::Traits::Container
                    <typename Long::Type, typename Long::Allocator>
{
  private: typedef
    typename LWF::Shortest::Signed::Integer<Short::maxSize>::Type Size;
  typedef LWF::Collection::Traits::Container
            <typename Long::Type, typename Long::Allocator> Base;
  public:

  typedef typename Base::Type       Type;
  typedef typename Base::Allocator  Allocator;
  typedef typename Long::Iterator   Iterator;
  struct Const { typedef typename Long::Const::Iterator Iterator; };

  public: UInt frontCapacity() const {
    return _long() ? (*_.long_).frontCapacity()
           : Short(typename Const::Iterator(*_.short_), _.size).frontCapacity();
  }
  public: UInt  backCapacity() const {
    return _long() ? (*_.long_). backCapacity()
           : Short(typename Const::Iterator(*_.short_), _.size). backCapacity();
  }

  public:Void ensureCapacity(UInt front, UInt back) {
    if (_long() ) { (*_.long_).ensureCapacity(front, back); }
    else { ensureShortCapacity(front, back); }
  }

  public: Void setCapacity(UInt front, UInt back) {
    if (_long() ) { (*_.long_).setCapacity(front, back); }
    else { ensureShortCapacity(front, back); }
  }

  private: Void ensureShortCapacity(UInt front, UInt back) {
    Short short_(*_.short_, _.size);
    if ((front + short_.size() + back) > short_.maxSize) {
      Long long_(Base::allocator());
      long_.ensureCapacity(front, short_.size() + back);
      long_.pushBack(short_.begin(), short_.end());
      short_.clear(); _.size = 0;
      newLong().swap(long_); _.size -= 1;
    }
  }

  public: Iterator first() const {
    return _long() ? (*_.long_).begin()
                : Short(typename Const::Iterator(*_.short_), _.size).begin();
  }
  Iterator last () const {
    return _long() ? (*_.long_).  end()
                : Short(typename Const::Iterator(*_.short_), _.size).  end();
  }

  protected: Iterator erase(const Iterator &first, const Iterator &last) {
    Iterator iterator;
    if (_long()) {
      iterator = (*_.long_).erase(first, last);
    } else {
       Short short_(*_.short_, _.size);
       { iterator = short_.erase(first, last); _.size = short_.size(); }
    }
    return iterator;
  }

  protected: template <typename RangeIterator>
  Iterator insert(const Iterator &position,
                  const RangeIterator &first, const RangeIterator &last) {
    Iterator iterator;
    if (_long()) {
      iterator = (*_.long_).insert(position, first, last);
    } else {
      Short short_(*_.short_, _.size);
      if (UInt(_.size) + (last - first) > short_.maxSize) {
        Long long_(Base::allocator()); {
          long_.pushBack(short_.begin(), position);
          long_.pushBack(first, last);
          long_.pushBack(position, short_.end());
        } { short_.clear(); _.size = 0; } {
          newLong().swap(long_); _.size -= 1;
        } iterator = (*_.long_).begin() + (position - short_.begin()) + (last - first);
      } else {
        { iterator = short_.insert(position, first, last); _.size = short_.size(); }
      }
    }
    return iterator;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  protected: Container(Container &&container)
    : Base(LWF::Forward::reference<Base>(container)) {
    raw = container.raw; container._.size = 0;
  }

  protected: Container &operator = (Container &&container) {
    Base::operator = (LWF::Forward::reference<Base>(container));
    LWF::swap(raw, container.raw);

    return *this;
  }
  #endif // C++11

  Void swap(Container &container) {
    LWF::swap<Base>(*this, container);
    LWF::swap(raw, container.raw);
  }

  protected: Container(const Allocator &allocator) : Base(allocator) {
    _.size = 0;
  }

  protected: ~Container() {
    if (_long()) { LWF::Placement::Deleter<Long>().Delete(&(*_.long_));
    } else { Short(*_.short_, _.size).clear(); }
  }

  protected: struct Capacity {
    UInt front, back;
    UInt size() const { return front + back; }
    Capacity(const Container &container)
      : front(container.frontCapacity()), back(container.backCapacity()) {}
  };

  private: Bool _long() const { return _.size < 0; }

  Long &newLong() {
    LWF::Placement::Allocator allocator(&(*_.long_));
    return *(new (allocator) Long(Base::allocator()));
  }

  private: struct Pack {
    union {
      LWF::Traits::Surrogate<Long> long_;
      LWF::Traits::Surrogate<Type[Short::maxSize]> short_;
    }; Size size;
  };

  private: struct Raw {
    UInt alignment[LWF::Type<Pack>::template Occupies<UInt>::items];
  };

  private: union { Raw raw; Pack _; };

  protected: struct Can {
    static const UInt fit = (sizeof(Raw) - sizeof(Size)) / sizeof(Type);
  };
};

} // namespace Traits

}}}} // namespace CShift::LWF::Collection::SCO


namespace CShift {
namespace LWF {

template <UInt size, typename Long>
struct SCO
  : LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::SCO::                    Traits::Container<
    LWF::Collection::SCO::Short::                     Container<
        typename Long::Type, size>, Long> > > > >
{
  private: typedef
    LWF::Collection::Dynamic::                        Container<
    LWF::Collection::Static::                         Container<
    LWF::Collection::Reversible::Array::High::Traits::Container<
    LWF::Collection::Dynamic   ::Array::High::Traits::Container<
    LWF::Collection::SCO::                    Traits::Container<
    LWF::Collection::SCO::Short::                     Container<
        typename Long::Type, size>, Long> > > > > Base;
  public:

  typedef typename Base::Type      Type;
  typedef typename Base::Allocator Allocator;

  SCO(const Allocator &allocator = Allocator()) : Base(allocator) {}

  SCO(UInt count, const Type &value = Type(),
      const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  SCO(const Iterator &first, const Iterator &last,
      const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  SCO(const Range &range, const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  SCO &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  SCO(const LWF::Initializer::List<Type> &list,
      const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  SCO &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  SCO (const SCO &sco, const Allocator &allocator = Allocator())
    : Base(sco, allocator) {}

  SCO &operator = (const SCO &sco) {
    Base::operator = (sco);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  SCO(SCO &&sco) : Base(LWF::Forward::reference<Base>(sco)) {}

  SCO &operator = (SCO &&sco) {
    Base::operator = (LWF::Forward::reference<Base>(sco));
    return *this;
  }
  #endif // C++11

  template <UInt words, UInt wordSize = sizeof(Void *),
            UInt should = words * wordSize,
            UInt is = sizeof(Base) > struct Can {
    static const UInt fit = (is < should ? Base::Can::fit + (should - is) / sizeof(Type) : size);
  };
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_SCO_H
