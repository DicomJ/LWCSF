#ifndef CSHIFT_LWF_LIST_H
#define CSHIFT_LWF_LIST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Std/Allocator.h"
#include "LWF/Custom/Allocator.h"
#include "LWF/Destroying/Deleter.h"
#include "LWF/Move/reference.h"
#include "LWF/Collection/Container.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Collection/Dynamic/Container.h"
#include "LWF/Value/Predicate/Equal/To.h"
#include "LWF/Traits/Countable/Size.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace List {

namespace Traits {

template <typename BBase, typename NBase, typename Size, typename Base>
struct Container : public Base, Size {

  private: struct Binder;
  private: struct Node;
  private: template <typename T> struct Is;
  public : typedef typename Base::Type Type;
  public : typedef typename Base::Allocator Allocator;
  public : struct Iterator;

  Iterator begin() const { return end() + 1;  }
  Iterator end  () const { return (typename Node::Link)root;  }

  Iterator erase(const typename Node::Iterator &iterator) {
    typename Node::Deleter deleter(pop(iterator->remove()), Base::allocator());
    return iterator + 1;
  }

  Iterator erase(const Iterator &first_, const Iterator &last) {
    Iterator first = first_;
    while (first != last) { first = erase(first); } return last;
  }

  template <typename Type>
  Iterator insert(const typename Node::Iterator &iterator, const Type &value) {
    return push(iterator, typename Node::Link(new (Base::allocator()) Node(value)));
  }

  template <typename RangeIterator>
  Iterator insert (const Iterator &iterator,
                   RangeIterator first, const RangeIterator &last) {
    if (first != last) {
      struct Chain : Container {
        Chain(const Allocator &allocator) : Container(allocator) { }
        ~Chain() { Container::erase(begin(), end()); }
      } chain(Base::allocator());
      UInt count = 0;
      for (; first != last; ++first, ++count) {
        chain.insert(chain.end(), *first);
      } (typename Node::Link(iterator))->chain(chain);
      static_cast<Size &>(*this) += count;
    }
    return iterator;// Next after last inserted
  }

  UInt maxSize() const { return Base::allocator().maxSize();  }

  Void resize(UInt size, const Type &value = Type()) {
    Iterator iterator = begin();
    while(size != 0 && iterator != end()) { ++iterator; --size; }
    if (0 == size) {
      erase(iterator, end());
    } else {
      typedef typename LWF::Value<const Type>::template Ptr<Int> Ptr;
      insert(iterator, Ptr(&value), Ptr(&value, size));
    }
  }

  Void swap(typename Node::Iterator one, const Iterator &other) {
    one->swap(other);
  }

  Void swap(Container &container) {
    LWF::swap<Size>(*this, container);
    LWF::swap<Base>(*this, container);
    LWF::swap(root, container.root);
  }

  Void splice(typename Node::Iterator position, Container &container,
              typename Node::Iterator first, const Iterator &last) {
    if (&container != this &&
        this->allocator() == container.allocator() &&
        first != last) {
      { UInt count = last - first;
        static_cast<Size &>(*this) += count;
        static_cast<Size &>(container) -= count;
      }
      position->insert(first, first->remove(last));
    }
  }

  template <typename Compare>
  Void merge(Container &container,
             const Iterator &first, const Iterator &last, Compare compare) {
    if (&container != this &&
        this->allocator() == container.allocator()) {
      Iterator position = begin(), iterator = first;
      while (position != end() && iterator != last) {
        if (compare(static_cast<const Type &>(*iterator),
                    static_cast<const Type &>(*position))) {
          push(position, container.pop(iterator++));
        } else { ++position; }
      }
      splice(position, container, container.begin(), container.end());
    }
  }

  Void reverse(const typename Node::Iterator &first,
               const typename Node::Iterator &last) {
    Iterator preFirst = Iterator(first) - 1;
    for (Iterator iterator = first; iterator != last;) {
      (typename Node::Iterator(iterator++))->reverse();
    } last->reverse(preFirst);
  }

  protected: Void slide(const typename Node::Iterator &position,
                        const typename Node::Iterator &node) {
    position->insert(node->remove());
  }

  protected: Node &expose(const typename Node::Link &node) const {
    return *node;
  }

  public: typename Node::Iterator pop(const typename Node::Iterator &node) {
    return --static_cast<Size &>(*this), node->remove();
  }
  protected: Iterator push(const typename Node::Iterator &position,
                       const typename Node::Iterator &node) {
    // Makes a difference to the STL
    return position->insert(node), ++static_cast<Size &>(*this), position;
  }

  protected: Container(const Allocator &allocator) : Base(allocator) {}
  public: template <typename U>
  Container(const U &u, const Allocator &allocator) : Base(u, allocator) {}

  private: operator typename Binder::Link () { return root; }

  private: struct Root; Root root;
};

template <typename BBase, typename NBase, typename SBase, typename Base>
template <typename T>
struct Container<BBase, NBase, SBase, Base>::Is {
  static const Bool Iterator =
      LWF::Type<T>::Is::Castable::template
            To<typename Container::Iterator>::type;
};

template <typename Base, typename NBase, typename SBase, typename CBase>
struct Container<Base, NBase, SBase, CBase>::Binder : virtual Base {

  typedef LWF::Weak::Ptr<typename Container::Node[]> Link;

  Void choke()               { prev = next = *this; }
  Void join      (Link node) { this->next = node; node->prev = *this; }
  Void substitute(Link node) { node->prev->join(*this); this->join(node->next); }
  Void reverse   (Link node) { LWF::swap(prev, node->next); }
  Void reverse()             { LWF::swap(prev, next); }
  Void insert    (Link node, Link before) { prev->join(node); before->join(*this); }
  Void insert    (Link node) { insert(node, node); }
  Void chain     (Link node) { insert(node->next, node->prev); node->choke(); }
  Link remove()              { prev->join(next); return *this; }
  Link remove     (Link at)  { Link before = at->prev; prev->join(at); return before; }
  Void swap      (Link node) { Binder This(*this); this->substitute(node);
                                                  node->substitute(This); }
  Binder(const Link &prev_ = null,
         const Link &next_ = null) : prev(prev_), next(next_){}

  operator Link() const {
    return reinterpret_cast<Node *>(const_cast<Binder *>(this));
  }
  operator Link() { return reinterpret_cast<Node *>(this); }

  Link prev, next;
};

template <typename BBase, typename Base, typename SBase, typename CBase>
struct Container<BBase, Base, SBase, CBase>::Node : Binder, virtual Base  {
  struct Iterator;
  typedef typename Container::Binder::Link Link;
  typedef typename Container::Allocator Allocator;
  struct Deleter : LWF::Unique::Ptr<Node,
                   LWF::Destroying::Deleter<Node, Allocator> > {
    Deleter(const Link &node, const Allocator &allocator) :
      LWF::Unique::Ptr<Node,
      LWF::Destroying::Deleter<Node, Allocator> >(&*node, allocator){}
  };

  ConstructionTransparency(Node, Base) {}
};

template <typename BBase, typename NBase, typename SBase, typename Base>
struct Container<BBase, NBase, SBase, Base>::Node::Iterator : Node::Link {

  typedef typename Base::Type Type;
  struct Unbiased { typedef typename Base::Type Type; };
  struct Return { typedef typename Iterator::Type &Type; };

  Type &operator * () const { return *static_cast<const Link &>(*this); }

  Int operator - (const Iterator &itr) const {
    Int distance = 0;
    for (Node::Link node = *this; node != itr; node = node->prev) { ++distance; }
    return distance;
  }

  Iterator operator + (Int index) const {
    Node::Link node = *this;
    if (index > 0) { for (;index != 0; --index) { node = node->next; }
    } else/* <= 0*/{ for (;index != 0; ++index) { node = node->prev; } }
    return Iterator(node);
  }

  Type &operator [] (Int index) const { return *(*this + index); }

  Iterator(const Node::Link &node = null) : Node::Link(node) { }
};

template <typename BBase, typename NBase, typename SBase, typename CBase>
struct Container<BBase, NBase, SBase, CBase>::Iterator
    : LWF::Ptr<typename Container::Node::Iterator> {
  protected: typedef LWF::Ptr<typename Container::Node::Iterator> Base;
  public:
  Iterator(const typename Node::Link &ptr = null) : Base(ptr){}
  WeaknessTransparency(Iterator, Base) {}
};

template <typename BBase, typename NBase, typename SBase, typename CBase>
struct Container<BBase, NBase, SBase, CBase>::Root : Container::Binder {

  typedef typename Container::Binder::Link Link;

  Void swap(Container::Binder &root) {
    { Link &prev = this->next->prev; prev = this->prev->next =  root; }
    { Link &prev = root. next->prev; prev = root. prev->next = *this; }
    LWF::swap(this->next, root.next);
    LWF::swap(this->prev, root.prev);
  }

  Root() { this->choke(); }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Root(Root &&root) { *this = LWF::Move::reference(root); }
  Root &operator = (Root &&root) {
    this->substitute(root); root.choke();
    return *this;
  }
  #endif // C++11
};

} // namespace Traits

struct Binder {};

template <typename Type>
struct Node : virtual LWF::Collection::List::Binder {

  Node(const Type &value) : value_(value)  {}
  Node &operator = (const Type &value)  { value_ = value; return *this; }
  Node(Type &value) : value_(value) {}
  Node &operator = (Type &value)  { value_ = value; return *this; }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Node(Type &&value) : value_(LWF::Forward::reference<Type>(value)) {}
  Node &operator = (Type &&value)  {
    value_ = LWF::Forward::reference<Type>(value); return *this;
  }
  #endif // C++11

  operator Type & () { return value_; }
  operator const Type & () const { return value_; }

  private: Type value_;
};

template <typename Type>
struct Allocator: LWF::Std::Allocator {
  Bool operator == (const Allocator &) { return True; }
  UInt maxSize() const {
    return (LWF::Type<UInt32>::max - LWF::Type<UInt8>::max) /
            LWF::Type<Type>::size;
  }
};

}}}} // namespace CShift::LWF::Collection::List


namespace CShift {
namespace LWF {

template <typename Type,
          typename Allocator = LWF::Collection::List::Allocator<Type>,
          Bool     countable = False>
struct List
  : LWF::Collection::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::List::Traits::Container<
    LWF::Collection::List::Binder,
    LWF::Collection::List::Node<Type>,
    LWF::Traits::Countable::Size<countable>,
    LWF::Collection::Traits::Container<Type, Allocator> > > >
{
  private: typedef
    LWF::Collection::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::List::Traits::Container<
    LWF::Collection::List::Binder,
    LWF::Collection::List::Node<Type>,
    LWF::Traits::Countable::Size<countable>,
    LWF::Collection::Traits::Container<Type, Allocator> > > > Base;
  public:

  struct Compare {
    static Bool Ascending (const Type &first, const Type &second) {
      return (first < second);
    }
    static Bool Descending(const Type &first, const Type &second) {
      return (first > second);
    }
  };

  Void reverse(const typename Base::Iterator &first,
               const typename Base::Iterator &last) {
    Base::reverse(first, last);
  }
  Void reverse(const typename Base::Reverse::Iterator &first,
               const typename Base::Reverse::Iterator &last) {
    Base::reverse(last, first);
  }
  Void reverse() { reverse(Base::begin(), Base::end()); }

  Void splice(const typename Base::Iterator &position, List &list,
              const typename Base::Iterator &first,
              const typename Base::Iterator &last) {
    Base::splice(position, list, first, last);
  }
  Void splice(const typename Base::Iterator &position, List &list,
              const typename Base::Reverse::Iterator &first,
              const typename Base::Reverse::Iterator &last) {
    typename Base::Reverse::Iterator first_ = last - 1;
    list.reverse(first, last);
    Base::splice(position, list, last, first_);
  }
  template <typename Iterator>
  Void splice(const typename Base::Iterator &position, List &list,
              const Iterator &iterator) {
    splice(position, list, iterator, iterator + 1);
  }
  Void splice(const typename Base::Iterator &position, List &list) {
    splice(position, list, list.begin(), list.end());
  }

  template <typename Compare>
  Void merge(List &list,
             const typename Base::Iterator &first,
             const typename Base::Iterator &last, Compare compare) {
    Base::merge(list, first, last, compare);
  }
  template <typename Compare>
  Void merge(List &list,
              const typename Base::Reverse::Iterator &first,
              const typename Base::Reverse::Iterator &last, Compare compare) {
    Base::merge(list, last, first, compare);
  }
  template <typename Compare>
  Void merge(List &list, Compare compare) {
    merge(list, list.begin(), list.end(), compare);
  }
  Void merge(List &list) { merge(list, Compare::Ascending); }

  template <typename Iterator>
  Void unique(const Iterator &first, const Iterator &last) {
    if (first != last) {
      for (Iterator value = first, iterator = value + 1; iterator != last;) {
        if (*value == *iterator) { iterator = Base::erase(iterator);
        } else { value = iterator++; }
      }
    }
  }
  Void unique() { unique(Base::begin(), Base::end()); }

  template <typename Predicate, typename Iterator>
  Void remove(Predicate predicate, Iterator first, const Iterator &last) {
    while (first != last) {
      if (predicate(static_cast<const Type &>(*first))) {
        first = Base::erase(first); } else { ++first; }
    }
  }
  template <typename Iterator>
  Void remove(const Type &value, const Iterator &first, const Iterator &last) {
      remove(typename LWF::Value<const Type>::Predicate::Equal::To(value),
             first, last);
  }
  template <typename Predicate>
  Void remove(Predicate predicate) {
    remove(predicate, Base::begin(), Base::end());
  }
  Void remove(const Type &value) {
    remove(value, Base::begin(), Base::end());
  }

  Void slide(const typename Base::Iterator &position,
            const typename Base::Iterator &iterator) {
    Base::slide(position, iterator);
  }
  Void slide(const typename Base::Reverse::Iterator &position,
            const typename Base::Reverse::Iterator &iterator) {
    Base::slide(position, iterator + 1);
  }

  template <typename Iterator, typename Compare>
  Iterator sorted(const Type &value, Compare compare,
                  Iterator first, const Iterator &last) const {
    for (;first != last; ++first) {
      if (compare(static_cast<const Type &>(value),
                  static_cast<const Type &>(*first))) break;
    } return first;
  }

  template <typename Compare>
  typename Base::Iterator sorted(const Type &value, Compare compare) {
    return sorted(value, compare, Base::begin(), Base::end());
  }
  typename Base::Iterator sorted(const Type &value) {
    return sorted(value, Compare::Ascending);
  }

  template <typename Iterator, typename Compare>
  Void sort(Compare compare, Iterator first, const Iterator &last) {
    if (first != last) {
      Iterator prevFirst = first - 1; // to avoid replacing of the first element
      for (Iterator value = first + 1; value != last; ) {
        Iterator position = sorted(*value, compare, prevFirst + 1, value);
        if (position != value) { slide(position, value++); } else { ++value; }
      }
    }
  }
  template <typename Compare>
  Void sort(Compare compare) { sort(compare, Base::begin(), Base::end()); }
  Void sort() { sort(Compare::Ascending); }

  List(const Allocator &allocator = Allocator()) : Base(allocator) {}

  List(UInt count, const Type &value = Type(),
            const Allocator &allocator = Allocator())
    : Base(count, value, allocator) { }

  template <typename Iterator>
  List(const Iterator &first, const Iterator &last, const Allocator &allocator = Allocator())
    : Base(first, last, allocator) { }

  template <typename Range>
  List(const Range &range,
       const Allocator &allocator = Allocator())
    : Base(range, allocator) {}

  template <typename Range>
  List &operator = (const Range &range) {
    Base::operator = (range);
    return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  List(const LWF::Initializer::List<Type> &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  List &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list);
    return *this;
  }
  #endif

  List(const List &list,
       const Allocator &allocator = Allocator())
    : Base(list, allocator) {}

  List &operator = (const List &list) {
    Base::operator = (list);
    return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  List(List &&list) : Base(LWF::Forward::reference<Base>(list)) {}

  List &operator = (List &&list) {
    Base::operator = (LWF::Forward::reference<Base>(list));
    return *this;
  }
  #endif // C++11
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_LIST_H
