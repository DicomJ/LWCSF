#ifndef CSHIFT_LWF_MULTI_SET_H
#define CSHIFT_LWF_MULTI_SET_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Binary/Search/RB/Tree.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Multi {
namespace Set {

template <typename Key>
struct Comparer :
LWF::Collection::Binary::Search::RB::Tree::Comparer<Key> {};

template <typename Type>
struct Allocator :
LWF::Collection::Binary::Search::RB::Tree::Allocator<Type> {};

}}} // namespace Collection::Multi::Set

namespace Multi {

template <typename Type,
          typename Comparer  = LWF::Collection::Multi::Set::Comparer<Type>,
          typename Allocator = LWF::Collection::Multi::Set::Allocator<Type>,
          Bool     countable = False>
struct Set
  : LWF::Binary::Search::RB::Tree<
      Type, True, Type, Comparer, Allocator, countable>
{
  private: typedef
    LWF::Binary::Search::RB::Tree<
      Type, True, Type, Comparer, Allocator, countable> Base;
  public:

  Set(const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(comparer, allocator) {}

  template <typename Iterator>
  Set(const Iterator &first, const Iterator &last,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(first, last, comparer, allocator) { }

  template <typename Range>
  Set(const Range &range,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(range, comparer, allocator) {}
  template <typename Range>
  Set &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Set(const LWF::Initializer::List<Type> &list,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(list, comparer, allocator) {}
  Set &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Set(const Set &set,
      const Comparer &comparer = Comparer(),
      const Allocator &allocator = Allocator())
    : Base(set, comparer, allocator) {}
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

} // namespace Multi
}} // namespace CShift::LWF

#endif // CSHIFT_LWF_MULTI_SET_H
