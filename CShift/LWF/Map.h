#ifndef CSHIFT_LWF_MAP_H
#define CSHIFT_LWF_MAP_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Binary/Search/RB/Tree.h"
#include "LWF/Collection/Associative/Pair.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Map {

template <typename Key>
struct Comparer :
LWF::Collection::Binary::Search::RB::Tree::Comparer<Key> {};

template <typename Type>
struct Allocator
: LWF::Collection::Binary::Search::RB::Tree::Allocator<Type> {};

}} // namespace Collection::Map

template <typename Key,
          typename T,
          typename Comparer  = LWF::Collection::Map::Comparer<Key>,
          typename Allocator = LWF::Collection::Map::Allocator<
                                 LWF::Collection::Associative::Pair<Key, T> >,
          Bool     countable = False>
struct Map
  : LWF::Binary::Search::RB::Tree<
      LWF::Collection::Associative::Pair<Key, T>,
      False, Key, Comparer, Allocator, countable>
{
  private: typedef
   LWF::Binary::Search::RB::Tree<
      LWF::Collection::Associative::Pair<Key, T>,
      False, Key, Comparer, Allocator, countable> Base;
  public: typedef typename Base::Type Type;

  T &at(const Key &key) {
    return (*Base::insert(Type(key)).iterator()).value();
  } T &operator [] (const Key &key) { return at(key); }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  T &at(Key &&key) {
    return (*Base::insert(Type(key)).iterator()).value();
  } T &operator [] (Key &&key) { return at(LWF::Forward::reference<Key>(key)); }
  #endif // C++11

  Map(const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(comparer, allocator) {}

  template <typename Iterator>
  Map(const Iterator &first, const Iterator &last,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(first, last, comparer, allocator) { }

  template <typename Range>
  Map(const Range &range,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(range, comparer, allocator) {}
  template <typename Range>
  Map &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Map(const LWF::Initializer::List<Type> &list,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(list, comparer, allocator) {}
  Map &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Map(const Map &map,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(map, comparer, allocator) {}
  Map &operator = (const Map &map) {
    Base::operator = (map); return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Map(Map &&map) : Base(LWF::Forward::reference<Base>(map)) {}
  Map &operator = (Map &&map) {
    Base::operator = (map); return *this;
  }
  #endif // C++11
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_MAP_H
