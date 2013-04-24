#ifndef CSHIFT_LWF_UNORDERED_MULTI_SET_H
#define CSHIFT_LWF_UNORDERED_MULTI_SET_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Hash/Chaining/Table.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Unordered {
namespace Multi {
namespace Set {

template <typename Key>
struct Hasher :
LWF::Collection::Hash::Chaining::Table::Hasher<Key> {};

template <typename Key>
struct Predicator :
LWF::Collection::Hash::Chaining::Table::Predicator<Key> {};

template <typename Type>
struct Allocator
: LWF::Collection::Hash::Chaining::Table::Allocator<Type> {};

}}}} // namespace Collection::Unordered::Multi::Set

namespace Unordered {
namespace Multi {

template <typename Type,
          typename Hasher     = LWF::Collection::Unordered::Multi::Set::Hasher<Type>,
          typename Predicator = LWF::Collection::Unordered::Multi::Set::Predicator<Type>,
          typename Allocator  = LWF::Collection::Unordered::Multi::Set::Allocator<Type>,
          LWF::Collection::Hash::Chaining::Table::Kind
                   kind       = LWF::Collection::Hash::Chaining::Table::vector/*|deque*/>
struct Set
  : LWF::Hash::Chaining::Table<
      Type, True, Type, Hasher, Predicator, Allocator, kind>
{
  private: typedef
    LWF::Hash::Chaining::Table<
      Type, True, Type, Hasher, Predicator, Allocator, kind> Base;
  public:

  Set(const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(hasher, predicator, allocator) {}

  template <typename Iterator>
  Set(const Iterator &first, const Iterator &last,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(first, last, hasher, predicator, allocator) { }

  template <typename Range>
  Set(const Range &range,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(range, hasher, predicator, allocator) {}
  template <typename Range>
  Set &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Set(const LWF::Initializer::List<Type> &list,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(list, hasher, predicator, allocator) {}
  Set &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Set(const Set &set,
      const Hasher &hasher = Hasher(),
      const Predicator &predicator = Predicator(),
      const Allocator &allocator = Allocator())
    : Base(set, hasher, predicator, allocator) {}
  Set &operator = (const Set &set) {
    Base::operator = (set); return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Set(Set &&set) : Base(LWF::Forward::reference<Base>(set)) {}
  Set &operator = (Set &&set) {
    Base::operator = (set); return *this;
  }
  #endif // C++11
};

}} // namespace Unordered::Multi
}} // namespace CShift::LWF

#endif // CSHIFT_LWF_UNORDERED_MULTI_SET_H
