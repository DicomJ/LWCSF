#ifndef CSHIFT_LWF_UNORDERED_MULTI_MAP_H
#define CSHIFT_LWF_UNORDERED_MULTI_MAP_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Hash/Chaining/Table.h"
#include "LWF/Collection/Associative/Pair.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Unordered {
namespace Multi {
namespace Map {

template <typename Key>
struct Hasher :
LWF::Collection::Hash::Chaining::Table::Hasher<Key> {};

template <typename Key>
struct Predicator :
LWF::Collection::Hash::Chaining::Table::Predicator<Key> {};

template <typename Type>
struct Allocator
: LWF::Collection::Hash::Chaining::Table::Allocator<Type> {};

}}}} // namespace Collection::Unordered::Multi::Map

namespace Unordered {
namespace Multi {

template <typename Key,
          typename Type,
          typename Hasher     = LWF::Collection::Unordered::Multi::Map::Hasher<Key>,
          typename Predicator = LWF::Collection::Unordered::Multi::Map::Predicator<Key>,
          typename Allocator  = LWF::Collection::Unordered::Multi::Map::Allocator<
                                  LWF::Collection::Associative::Pair<Key, Type> >,
          LWF::Collection::Hash::Chaining::Table::Kind
                   kind       = LWF::Collection::Hash::Chaining::Table::vector/*|deque*/>
struct Map
  : LWF::Hash::Chaining::Table<
      LWF::Collection::Associative::Pair<Key, Type>,
      True, Key, Hasher, Predicator, Allocator, kind>
{
  private: typedef
    LWF::Hash::Chaining::Table<
      LWF::Collection::Associative::Pair<Key, Type>,
      True, Key, Hasher, Predicator, Allocator, kind> Base;
  public:

  Map(const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(hasher, predicator, allocator) {}

  template <typename Iterator>
  Map(const Iterator &first, const Iterator &last,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(first, last, hasher, predicator, allocator) { }

  template <typename Range>
  Map(const Range &range,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(range, hasher, predicator, allocator) {}
  template <typename Range>
  Map &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Map(const LWF::Initializer::List<Type> &list,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(list, hasher, predicator, allocator) {}
  Map &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Map(const Map &map,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(map, hasher, predicator, allocator) {}
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

}} // namespace Unordered::Multi
}} // namespace CShift::LWF

#endif // CSHIFT_LWF_UNORDERED_MULTI_MAP_H
