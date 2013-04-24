#ifndef CSHIFT_LWF_FORWARD_LIST_H
#define CSHIFT_LWF_FORWARD_LIST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Std/Allocator.h"
#include "LWF/Custom/Allocator.h"
#include "LWF/Traits/Countable/Size.h"
#include "LWF/Destroying/Deleter.h"
#include "LWF/Collection/Container.h"
#include "LWF/Collection/Static/Forward/Container.h"
#include "LWF/Collection/Dynamic/Forward/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Forward {
namespace List {

namespace Traits {

template <typename BBase, typename NBase, typename Size, typename Base>
struct Container : public Base, Size {

  private: struct Binder;
  private: struct Node;
  public : typedef typename Base::Type Type;
  public : typedef typename Base::Allocator Allocator;
  public : struct Iterator;

  protected: struct Reverse { struct Iterator; };

  protected: typename Reverse::Iterator rbegin() const { return end(); }
  public   : typename Reverse::Iterator rend  () const { return typename Node::Link(root); }
  public   : Iterator begin() const { return root.next;  }
  public   : Iterator end  () const { return typename Node::Link(null); }

  Iterator erase(const typename Node::Iterator &before) {
    typename Node::Deleter deleter(pop(before), Base::allocator());
    return before;
  }

  Iterator erase(const Iterator &before, const Iterator &last) {
    while(before + 1 != last) { erase(before); } return before;
  }

  template <typename Type>
  Iterator insert(typename Node::Iterator iterator, const Type &value) {
    return push(iterator, typename Node::Link(new (Base::allocator()) Node(value)));
  }

  template <typename RangeIterator>
  Iterator insert (typename Node::Iterator before,
                   RangeIterator first, const RangeIterator &last) {
    if (first != last) {
      struct Chain : Container {
        Chain(const Allocator &allocator) : Container(allocator) { }
        ~Chain() { Container::erase(Iterator(rend()), end()); }
      } chain(Base::allocator());
      Iterator iterator = chain.rend();
      UInt count = 0;
      for (;first != last; ++first, ++count) {
        iterator = chain.insert(iterator, *first);
      } before = (typename Node::Link(before))->chain(chain, iterator);
      static_cast<Size &>(*this) += count;
    } return before;
  }

  UInt maxSize() const { return Base::allocator().maxSize();  }

  Void resize(UInt size, const Type &value = Type()) {
    Iterator before = end();
    while(size != 0 && before + 1 != end()) { ++before; --size; }
    if (0 == size) {
      erase(before, end());
    } else {
      typedef typename LWF::Value<const Type>::template Ptr<Int> Ptr;
      insert(before, Ptr(&value), Ptr(&value, size));
    }
  }

  Void swap(typename Node::Iterator beforeOne, const Iterator &beforeOther) {
    beforeOne->swap(beforeOther);
  }

  Void swap(Container &container) {
    LWF::swap<Size>(*this, container);
    LWF::swap<Base>(*this, container);
    LWF::swap(root, container.root);
  }

  protected: Void reverse(const Iterator &before,
                          const Iterator &last) {
    Iterator prev = before + 1;
    if (prev != last) {
      Iterator first = prev;
      for (Iterator iterator = first + 1; iterator != last;) {
        (typename Node::Link(iterator++))->reverse(prev++);
      } (typename Node::Link(before))->reverse(prev);
      (typename Node::Link(first))->reverse(last);
    }
  }

  protected: Iterator pop(const typename Node::Iterator &before) {
    --static_cast<Size &>(*this);
    return before->remove();
  }
  protected: Iterator push(const typename Node::Iterator &after,
                           const typename Node::Iterator &node) {
    ++static_cast<Size &>(*this);
    return after->insert(node);
  }

  Iterator slide(const typename Node::Iterator &after,
                 const typename Node::Iterator &before) {
    return after->insert(before->remove());
  }

  protected: Iterator erase(const typename Reverse::Iterator &before,
                 const typename Reverse::Iterator &last) {
    return erase(static_cast<const Iterator &>(last),
                 static_cast<const Iterator &>(before));
  }

  protected: Container(const Allocator &allocator) : Base(allocator), root() {}

  protected: operator typename Binder::Link () { return root; }

  private: struct Root; Root root;
};

template <typename Base, typename NBase, typename SBase, typename CBase>
struct Container<Base, NBase, SBase, CBase>::Binder : virtual Base {

  typedef LWF::Weak::Ptr<typename Container::Node[]> Link;

  Link insert(const Link &node) { node->next = next; return next = node; }
  Link remove() { Link next = this->next; this->next = next->next; return next; }
  Void swap(const Link &node) {
    LWF::swap(this->next->next, node->next->next);
    LWF::swap(this->next, node->next);
  }
  Void reverse(const Link prev) { next = prev; }
  Link chain(const Link &before, const Link &last) {
    last->next = next; next = before->next; before->next = null; return last;
  }

  operator Link() const {
    return reinterpret_cast<Node *>(const_cast<Binder *>(this));
  }

  operator Link() { return reinterpret_cast<Node *>(this); }

  Link next;
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

  Iterator operator + (UInt index) const {
    Node::Link node = *this;
    for (;index != 0; --index) { node = node->next; }
    return Iterator(node);
  }

  Int operator - (const Iterator &itr) const {
    Int distance = 0;
    for (Node::Link node = itr; node != *this; node = node->next) { ++distance; }
    return distance;
  }

  Type &operator [] (Int index) const { return *(*this + index); }

  Iterator(const Node::Link &node = null) : Node::Link(node) { }
};

template <typename BBase, typename NBase, typename SBase, typename CBase>
struct Container<BBase, NBase, SBase, CBase>::Iterator
    : LWF::Ptr<typename Container::Node::Iterator> {
  protected: typedef LWF::Ptr<typename Container::Node::Iterator> Base;
  public: Iterator(const Base &base) : Base(base) {}
  public: Iterator &operator = (const Base &base) {
    Base::operator = (base); return *this;
  }
  public: Iterator(const typename Node::Link &ptr = null) : Base(ptr){}

  Iterator operator + (UInt index) const { return Base::operator + (index); }
  Iterator& operator += (UInt index) { return Base::operator += (index), *this; }
  UInt operator - (const Iterator & iterator) const {
    return Base::operator - (iterator);
  }
  private: Iterator  operator -  (Int) const;
  private: Iterator& operator -= (Int);
  private: Iterator& operator -- ();
  private: Iterator  operator -- (Int32);
};

template <typename BBase, typename NBase, typename SBase, typename CBase>
struct Container<BBase, NBase, SBase, CBase>::Reverse::Iterator : Container::Iterator {
  Iterator(const typename Node::Link &node) :
    Container::Iterator(typename Node::Iterator(node)) {}
  Container::Iterator operator - (Int) const { return *this; }
};

template <typename BBase, typename NBase, typename SBase, typename CBase>
struct Container<BBase, NBase, SBase, CBase>::Root : Container::Binder {

  Void swap(Container::Binder &root) {
    LWF::swap(this->next, root.next);
  }

  Root() {}

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Root(Root &&root) { *this = LWF::Move::reference(root); }
  Root &operator = (Root &&root) {
    this->next = root.next;
    root.next = null;
    return *this;
  }
  #endif // C++11

};

} // namespace Traits

struct Binder {};

template <typename Type>
struct Node : virtual LWF::Collection::Forward::List::Binder {

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

}}}}} // namespace CShift::LWF::Collection::Forward::List


namespace CShift {
namespace LWF {
namespace Forward {

template <typename Type,
          typename Allocator = LWF::Collection::Forward::List::Allocator<Type>,
          Bool     countable = False>
struct List
  : LWF::Collection::Dynamic::Forward::Container<
    LWF::Collection::Static::Forward::Container<
    LWF::Collection::Forward::List::Traits::Container<
    LWF::Collection::Forward::List::Binder,
    LWF::Collection::Forward::List::Node<Type>,
    LWF::Traits::Countable::Size<countable>,
    LWF::Collection::Traits::Container<Type, Allocator> > > >
{
  private: typedef
    LWF::Collection::Dynamic::Forward::Container<
    LWF::Collection::Static::Forward::Container<
    LWF::Collection::Forward::List::Traits::Container<
    LWF::Collection::Forward::List::Binder,
    LWF::Collection::Forward::List::Node<Type>,
    LWF::Traits::Countable::Size<countable>,
    LWF::Collection::Traits::Container<Type, Allocator> > > > Base;
  public:

  typedef typename Base::Iterator Iterator;

  struct Compare {
    static Bool Ascending (const Type &first, const Type &second) {
      return (first < second);
    }
    static Bool Descending(const Type &first, const Type &second) {
      return (first > second);
    }
  };

  Iterator rend() const { return Base::rend(); }

  Void reverse(const Iterator &before, const Iterator &last) {
    return Base::reverse(before, last);
  }
  Void reverse() { reverse(rend(), Base::end()); }

  Void splice(Iterator after, List &list,
              const Iterator &before, const Iterator &last) {
    if (&list != this && this->allocator() == list.allocator()) {
      while(before + 1 != last) {
        after = Base::push(after, list.pop(before));
      }
    }
  }
  Void splice(const Iterator &after, List &list, const Iterator &before) {
    splice(after, list, before, before + 2);
  }
  Void splice(const Iterator &after, List &list) {
    splice(after, list, list.rend(), list.end());
  }

  template <typename Compare>
  Void merge(List &list,
             Iterator before, const Iterator &last, Compare compare) {
    if (&list != this && this->allocator() == list.allocator()) {
      Iterator after = rend();
      while (after + 1 != Base::end() && before + 1 != last) {
        if (compare(static_cast<const Type &>(*(before + 1)),
                    static_cast<const Type &>(*(after + 1)))) {
          after = Base::push(after, list.pop(before));
        } else { ++after; }
      }
      splice(after, list, list.rend(), list.end());
    }
  }
  template <typename Compare>
  Void merge(List &list, Compare compare) {
    merge(list, list.rend(), list.end(), compare);
  }
  Void merge(List &list) { merge(list, Compare::Ascending); }

  template <typename Iterator>
  Void unique(Iterator before, const Iterator &last) {
    if (before + 1 != last) {
      for (Iterator value = before, iterator = value + 1; iterator + 1 != last;) {
        if (*(value + 1)== *(iterator + 1)) { Base::erase(iterator);
        } else { value = iterator++; }
      }
    }
  }
  Void unique() { unique(rend(), Base::end()); }

  template <typename Predicate>
  Void remove(Predicate predicate, Iterator before, const Iterator &last) {
    while (before + 1 != last) {
      if (predicate(static_cast<const Type &>(*(before + 1))))
      { Base::erase(before); } else { ++before; }
    }
  }
  template <typename Predicate>
  Void remove(Predicate predicate) {
    remove(predicate, rend(), Base::end());
  }
  Void remove(const Type &value, const Iterator &before, const Iterator &last) {
      remove(typename LWF::Value<const Type>::Predicate::Equal::To(value),
             before, last);
  }
  Void remove(const Type &value) {
    remove(value, rend(), Base::end());
  }

  template <typename Compare>
  Iterator sorted(const Type &value, Compare compare,
                  Iterator before, const Iterator &last) const {
    for (;before + 1 != last; ++before) {
      if (compare(static_cast<const Type &>(value),
                  static_cast<const Type &>(*(before + 1)))) break;
    } return before;
  }

  template <typename Compare>
  Iterator sorted(const Type &value, Compare compare) {
    return sorted(value, compare, rend(), Base::end());
  }
  Iterator sorted(const Type &value) {
    return sorted(value, Compare::Ascending);
  }

  template <typename Iterator, typename Compare>
  Void sort(Compare compare, const Iterator &before, const Iterator &last) {
    if (before + 1 != last) {
      for (Iterator value = before + 1; value + 1 != last; ) {
        Iterator position = sorted(*(value + 1), compare, before, value + 1);
        if (position != value) { value = Base::slide(position, value); } else { ++value; }
      }
    }
  }
  template <typename Compare>
  Void sort(Compare compare) { sort(compare, rend(), Base::end()); }
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

}}} // namespace CShift::LWF::Forward

#endif // CSHIFT_LWF_FORWARD_LIST_H
