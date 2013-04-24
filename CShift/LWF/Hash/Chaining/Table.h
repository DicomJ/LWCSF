#ifndef CSHIFT_LWF_HASH_CHAINING_TABLE_H
#define CSHIFT_LWF_HASH_CHAINING_TABLE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Hasher.h"
#include "LWF/List.h"
#include "LWF/Vector.h"
#include "LWF/Deque.h"
#include "LWF/Range.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Algorithm/min.max.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Collection/Associative/Container.h"
#include "LWF/Collection/Associative/Dynamic/Container.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Hash {
namespace Chaining {
namespace Table {

template <typename Base, typename Buckets, typename Factor_>
struct Container : Base {
  protected: struct As;
  public   : typedef Factor_ Factor;
  public   : typedef typename Base::Type Type;
  public   : typedef typename Base::Key Key;
  public   : typedef typename Base::Predicator Predicator;
  public   : typedef typename Base::Hasher Hasher;
  public   : typedef typename Hasher::Type Hash;
  public   : typedef typename Base::Comparer Comparer;
  public   : typedef typename Base::Allocator Allocator;
  public   : typedef typename Base::Iterator Iterator;
  public   : typedef typename Base::Insert Insert;

  template <typename T>
  typename Insert::template Result<Iterator>
  insert(const Iterator &/*hint*/, const T &value) {
    if (maxElements <= Base::size()) {
      rehash(LWF::max(UInt(expanse * Base::size()), Base::size() + 1));
    }
    typename As::Key::template Bucket<Container>
           bucket(*this, static_cast<const Type &>(value));
    return bucket.insert(value);
  }

  Void erase(const Iterator &iterator) {
    typename As::Hash::template Bucket<Container>
    bucket(*this, Base::expose(iterator)(hasher()));
    bucket.erase(iterator);
  }

  UInt erase(const Key &key) {
    typename As::Key::template Bucket<Container> bucket(*this, key);
    return bucket.clear();
  }

  Iterator find(const Key &key) const {
    return typename As::Key::template Bucket<const Container>(*this, key).find();
  }

  UInt count(const Key &key) const {
    return typename As::Key::template Bucket<const Container>(*this, key).count();
  }

  LWF::Range<Iterator> equalRange(const Key &key) const {
    //!!!NOTICE: this method as well as an approprivate
    // std::unordered_map::equal_range method may not return the all values
    // which match the key (as the specification says).
    // It just guarantees that all values in the range it returns match the key.
    return  typename As::Key::template
            Bucket<const Container>(*this, key).equalRange();
  }

  UInt bucketSize(UInt bucket) const { return typename
    As::Index::template Bucket<const Container>(*this, bucket).size();
  }

  UInt bucketCount() const { return buckets.size(); }

  UInt maxBucketCount() const { return Base::allocator().maxSize(); }

  Factor loadFactor() const {
    return Factor(Base::size()) / bucketCount();
  }

  Factor maxLoadFactor() const { return factor; }

  Void maxLoadFactor(const Factor &factor) {
    this->factor = LWF::max(Factor(1) / maxBucketCount(), factor);
    rehash(UInt(Factor(Base::size()) / this->factor));
  }

  Factor expansionFactor() const { return expanse; }

  Void expansionFactor(const Factor &factor) {
    if (factor > Factor(1)) { expanse = factor; }
  }

  Void reserve(UInt elements) {
    if (elements > maxElements) { rehash(elements / factor); }
  }

  Void rehash(UInt buckets) {
    if (buckets >  bucketCount()) {
      this->buckets.clear();
      this->buckets.resize(buckets, Base::end());

      { // Reconstruction
        Base base(Base::comparer(), Base::allocator());
        LWF::swap<Base>(base, *this);
        while (base.begin() != base.end()) {
          typename As::Hash::template Bucket<Container> bucket
              (*this, Base::expose(base.begin())(hasher()));
          bucket.push(base.pop(base.begin()));
        }
      } maxElements = UInt(factor * bucketCount());
    }
  }

  Void clear() {
    Base::erase(Base::begin(), Base::end());
    LWF::range(buckets).fill(Base::end());
  }

  const typename Base::Comparer::Hasher &hasher() const {
    return Base::comparer().hasher();
  }
  typename Base::Comparer::Hasher &hasher() {
    return Base::comparer().hasher();
  }

  const typename Base::Comparer::Predicator &comparer() const {
    return Base::comparer().predicator();
  }
  typename Base::Comparer::Predicator &comparer() {
    return Base::comparer().predicator();
  }

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator),
      buckets(typename Buckets::Allocator(allocator)),
      maxElements(0), factor(1/*0.75 == Factor(3)/4 */), expanse(2) {
    rehash(8);
  }

  private: Buckets buckets;
  private: UInt maxElements; Factor factor, expanse;
};


template <typename CBase, typename Buckets, typename Factor>
struct Container<CBase, Buckets, Factor>::As {

  struct Index {

    template <typename Container>
    struct Bucket {

      private: struct Find;
      private: struct Count;
      public: typedef typename CBase::Key Key;

      Bucket(Container &This_, UInt index_)
        : This(This_),
          index(index_),
          begin(index + 0 < This.bucketCount() ?
                            This.buckets[index + 0] :  This.end()),
          end  (index + 1 < This.bucketCount() ?
                            This.buckets[index + 1] :  This.end()) {}

      UInt size() const { return end - begin; }
      Bool empty() const { return end == begin; }

      Void erase(const Iterator &iterator) {
        const Iterator next = This.CBase::erase(iterator);
        if (begin == iterator) { slide(next); }
      }

      UInt clear(const Key &key) {
        if (Container::multi) {
          const UInt count = This.CBase::size();
          Iterator begin, last = begin = this->begin;
          while (begin != end) {
            begin = find_(key, begin        );
            if (begin != end) {
              Iterator next = This.CBase::erase(begin);
              if (last == begin) { last = next; }
              begin = next;
            }
          } slide(last);
          return count - This.CBase::size();
        } else {
          const Iterator iterator = find(key);
          UInt count = (iterator != This.end() ? 1 : 0);
          erase(iterator);
          return count;
        }
      }

      Void push(const Iterator &iterator) { // reconstruction
        This.CBase::push(end, iterator);
        if (empty()) { slide(iterator); }
      }

      template <typename T>
      typename Container::Insert::template Result<Iterator>
      insert(const T &value, const typename Container::Hash &hash) {
        Iterator iterator;
        Bool isNew = Container::multi ||
                     (This.end() == (iterator =
                                     find(static_cast<const Type &>(value))));
        if (isNew) {
          iterator = This.CBase::insert(end, value) + -1;
          This.CBase::expose(iterator) = hash;
          if (empty()) { slide(iterator); }
        } return typename
            Container::Insert::template Result<Iterator>(iterator, isNew);
      }

      LWF::Range<Iterator> equalRange(const Key &key) const {
        const Iterator begin = find_(key);
        if (end == begin)  {
          return LWF::Range<Iterator>(This.end(), This.end());
        } else {
          Iterator end;
          for (end = begin + 1; end != this->end &&
               This.comparer()(key, static_cast<const Type &>(*end)); ++end) {}
          return LWF::Range<Iterator>(begin, end);
        }
      }

      Iterator find(const Key &key) const {
        Iterator begin = find_(key); return begin != end ? begin: This.end();
      }

      UInt count(const Key &key) const {
        UInt number = 0; Count count(This.comparer(), key, &number);
        LWF::range(begin, end).till(count);
        return number;
      }

      private: Iterator find_(const Key &key) const {
        return find_(key, begin);
      }

      private: Iterator find_(const Key &key, const Iterator &begin) const {
        return LWF::range(begin, end).find(Find(This.comparer(), key));
      }

      private: struct Find {
        Find(const Predicator &predicator_, const Key &key_)
          : predicator(predicator_), key(key_) {}
        Bool operator() (const Key &key) { return predicator(this->key, key); }
        const Predicator &predicator;
        const Key &key;
      };

      private: struct Count : Find {
        Count(const Predicator &predicator, const Key &key,
              LWF::Weak::Ptr<UInt> number_) :
          Find(predicator, key), number(number_) {}

        Bool operator()(const Key &key) {
          Find &find = *this; if (find(key)) { ++*number; } return True;
        }

        LWF::Weak::Ptr<UInt> number;
      };

      protected: Void slide(const Iterator &next) {
        for (UInt i = index; i != UInt(-1) && begin == This.buckets[i]; --i) {
          This.buckets[i] = next;
        }
      }

      protected: Container &This;
      protected: const UInt index;
      protected: const Iterator begin;
      protected: const Iterator end;
    };
  };

  struct Hash {
    template <typename Container>
    struct Bucket : Index::template Bucket<Container> {
      private: typedef typename Index::template Bucket<Container> Base; public:
      Bucket(Container &This, const typename Container::Hash &hash_)
        : Base(This, UInt(hash_) % This.bucketCount()), hash(hash_) {}

      template <typename T>
      typename Container::Insert::template Result<Iterator>
      insert(const T &value) { return Base::insert(value, hash); }

      protected: const typename Container::Hash hash;
    };
  };

  struct Key {
    template <typename Container>
    struct Bucket : Hash::template Bucket<Container> {
      private: typedef typename Hash::template Bucket<Container> Base; public:
      Bucket(Container &This, const typename Container::Key &key_)
        : Base(This, This.hasher()(key_)), key(key_) {}

      UInt clear() { return Base::clear(key); }
      Iterator find() const { return Base::find(key); }
      UInt count() const { return Base::count(key); }
      LWF::Range<Iterator> equalRange() const { return Base::equalRange(key); }

      protected: const typename Container::Key &key;
    };
  };
};

struct Binder : virtual LWF::Collection::List::Binder {};

template <typename Type, typename Hasher, Bool = Hasher::cache>
struct Node : virtual LWF::Collection::Hash::Chaining::Table::Binder,
              LWF::Collection::List::Node<Type> {
  private: typedef LWF::Collection::List::Node<Type> Base;
  public: typedef typename Hasher::Type Hash;

  Hash operator ()(const Hasher &hasher) const {
    return hasher(static_cast<const Type &>(*this));
  }
  Node &operator = (const Hash &) { return *this; }

  ConstructionTransparency(Node, Base) {}
};

template <typename Type, typename Hasher>
struct Node<Type, Hasher, !False> : Node<Type, Hasher, False> {

  private: typedef Node<Type, Hasher, False> Base;
  public: typedef typename Base::Hash Hash;

  Hash operator ()(const Hasher &) const { return hash; }
  Node &operator = (const Hash &hash) { this->hash = hash; return *this; }

  ConstructionTransparency(Node, Base) {}
  private: Hash hash;
};

template <typename Key>
struct Hasher : LWF::Hasher<Key> {};

template <typename Key>
struct Predicator {
  Bool operator()(const Key &a, const Key &b) const { return a == b; }
};

template <typename Hasher_, typename Predicator_>
struct Comparer : Hasher_, Predicator_ {
  typedef Hasher_     Hasher;
  typedef Predicator_ Predicator;
  Comparer() {}
  Comparer(const Hasher &hasher, const Predicator &predicator)
    : Hasher(hasher), Predicator(predicator) {}

  const Hasher &hasher() const { return *this; }
  Hasher &hasher() { return *this; }

  const Predicator &predicator() const { return *this; }
  Predicator &predicator() { return *this; }

  Void swap(Comparer &comparer) {
    LWF::swap<Hasher>(*this, comparer);
    LWF::swap<Predicator>(*this, comparer);
  }
};

template <typename Type>
struct Allocator: LWF::Std::Allocator {
  Bool operator == (const Allocator &) { return True; }
  UInt maxSize() const {
    return (LWF::Type<UInt32>::max - LWF::Type<UInt8>::max) /
                LWF::Type<Type>::size;
  }
  struct Rebind {
    template <typename Base>
    struct With : Base {
      With(const Allocator &) {}
      UInt expanse(UInt/* capacity*/, UInt/* count*/, UInt/* size*/) const {
        return 0;
      }
    };
  };
};

template <typename Type, typename Allocator>
struct Deque {
  typedef typename Allocator::Rebind::template With<
      LWF::Collection::Reversible::Deque::Allocator<Type, 64> > Allocator_;
  typedef LWF::Deque<Type,  Allocator_> Buckets;
};

template <typename Type, typename Allocator>
struct Vector {
  typedef typename Allocator::Rebind::template With<
      LWF::Collection::Reversible::Vector::Allocator<Type> > Allocator_;
  typedef LWF::Vector<Type,  Allocator_> Buckets;
};

enum Kind { vector, deque };
template <Kind, typename Type, typename Allocator> struct Buckets;
template <typename T, typename Allocator> struct Buckets<vector, T, Allocator> {
  typedef typename LWF::Collection::Hash::Chaining::Table::template
    Vector<T, Allocator>::Buckets Type;
};
template <typename T, typename Allocator> struct Buckets<deque, T, Allocator> {
  typedef typename LWF::Collection::Hash::Chaining::Table::template
    Deque<T, Allocator>::Buckets Type;
};

namespace Factor {
  // Might be a Fixed::Point for the embeded systems
  typedef Float Type;
  // TODO: make this a platform specific!!!
} // namespace Factor

}}}} // namespace Collection::Hash::Chaining::Table

namespace Hash {
namespace Chaining {

template <
  typename Type,
  Bool     multi      = False,
  typename Key        = Type,
  typename Hasher     = LWF::Collection::Hash::Chaining::Table::Hasher<Key>,
  typename Predicator = LWF::Collection::Hash::Chaining::Table::Predicator<Key>,
  typename Allocator  = LWF::Collection::Hash::Chaining::Table::Allocator<Type>,
  LWF::Collection::Hash::Chaining::Table::Kind
           kind       = LWF::Collection::Hash::Chaining::Table::vector/*|deque*/,
  typename Factor     = LWF::Collection::Hash::Chaining::Table::Factor::Type>
struct Table
  : LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::Hash::Chaining::Table::Container<
    LWF::Collection::List::Traits::Container<
      LWF::Collection::Hash::Chaining::Table::Binder,
      LWF::Collection::Hash::Chaining::Table::Node<Type, Hasher>,
      LWF::Traits::Countable::Size<True>,
      LWF::Collection::Associative::Container<
        Type, Key,
        LWF::Collection::Hash::Chaining::Table::Comparer<Hasher, Predicator>,
        multi, Allocator> >,
      typename LWF::Collection::Hash::Chaining::Table::Buckets<kind, typename
        LWF::Collection::List::Traits::Container<
          LWF::Collection::Hash::Chaining::Table::Binder,
          LWF::Collection::Hash::Chaining::Table::Node<Type, Hasher>,
          LWF::Traits::Countable::Size<True>,
          LWF::Collection::Associative::Container< Type, Key,
          LWF::Collection::Hash::Chaining::Table::Comparer<
            Hasher, Predicator>, multi, Allocator> >::Iterator,
        Allocator>::Type, Factor> > >
{
  public: typedef
    LWF::Collection::Hash::Chaining::Table::Comparer<Hasher, Predicator> Comparer;
  private: typedef
    LWF::Collection::List::Traits::Container<
      LWF::Collection::Hash::Chaining::Table::Binder,
      LWF::Collection::Hash::Chaining::Table::Node<
        Type, Hasher>,
      LWF::Traits::Countable::Size<True>,
      LWF::Collection::Associative::Container<
        Type, Key, Comparer, multi, Allocator> > Chain;
  private: typedef
    typename LWF::Collection::Hash::Chaining::Table::Buckets<
      kind, typename Chain::Iterator, Allocator>::Type Buckets;
  private: typedef
    LWF::Collection::Hash::Chaining::Table::Container<
      Chain, Buckets, Factor> Chaining;
  private: typedef
    LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<Chaining> > Base;
  public:

  Table(const Hasher &hasher = Hasher(),
        const Predicator &predicator = Predicator(),
        const Allocator &allocator = Allocator())
    : Base(Comparer(hasher, predicator), allocator) {}

  template <typename Iterator>
  Table(const Iterator &first, const Iterator &last,
       const Hasher &hasher = Hasher(),
       const Predicator &predicator = Predicator(),
       const Allocator &allocator = Allocator())
    : Base(first, last, Comparer(hasher, predicator), allocator) { }

  template <typename Range>
  Table(const Range &range,
        const Hasher &hasher = Hasher(),
        const Predicator &predicator = Predicator(),
        const Allocator &allocator = Allocator())
    : Base(range, Comparer(hasher, predicator), allocator) {}
  template <typename Range>
  Table &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Table(const LWF::Initializer::List<Type> &list,
        const Hasher &hasher = Hasher(),
        const Predicator &predicator = Predicator(),
        const Allocator &allocator = Allocator())
    : Base(list, Comparer(hasher, predicator), allocator) {}
  Table &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Table(const Table &table,
        const Hasher &hasher = Hasher(),
        const Predicator &predicator = Predicator(),
        const Allocator &allocator = Allocator())
    : Base(table, Comparer(hasher, predicator), allocator) {}
  Table &operator = (const Table &table) {
    Base::operator = (table); return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Table(Table &&table) : Base(LWF::Forward::reference<Base>(table)) {}
  Table &operator = (Table &&table) {
    Base::operator = (table); return *this;
  }
  #endif // C++11
};

}} // namespace Hash::Chaining

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_HASH_CHAINING_TABLE_H
