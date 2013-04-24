#ifndef CSHIFT_LWF_BINARY_SEARCH_TREE_H
#define CSHIFT_LWF_BINARY_SEARCH_TREE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Algorithm/swap.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Unique/Ptr.h"
#include "LWF/Destroying/Deleter.h"
#include "LWF/Collection/Static/Container.h"
#include "LWF/Collection/Associative/Container.h"
#include "LWF/Collection/Associative/Dynamic/Container.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Binary {
namespace Search {
namespace Tree {

namespace High {
namespace Traits {

template <typename Base, Bool = Base::multi>
struct Container : Base {
  typedef typename Base::Key Key;
  typedef typename Base::Comparer Comparer;
  typedef typename Base::Allocator Allocator;
  typedef typename Base::Iterator Iterator;

  UInt erase(const Key &key) {
    Iterator begin = Base::find(key);
    UInt count = 0;
    for (; begin != Base::end() && 0 == Base::comparer()(*begin, key); ++count) {
        erase(begin++);
    } return count;
  }

  Void erase(const Iterator &iterator) { Base::erase(iterator); }

  UInt count(const Key &key) const {
    Iterator begin = Base::find(key);
    UInt count = 0;
    for (; begin != Base::end() && 0 == Base::comparer()(*begin, key); ++begin) {
        ++count;
    } return count;
  }

  LWF::Range<Iterator> equalRange(const Key &key) const {
    return LWF::Range<Iterator>(Base::lowerBound(key), Base::upperBound(key));
  }

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}
};

template <typename Base>
struct Container<Base, False> : Base {
  typedef typename Base::Key Key;
  typedef typename Base::Comparer Comparer;
  typedef typename Base::Allocator Allocator;
  typedef typename Base::Iterator Iterator;

  UInt erase(const Key &key) {
    Iterator begin = Base::find(key);
    return (begin != Base::end()) ? (erase(begin), 1) : 0;
  }

  Void erase(const Iterator &iterator) { Base::erase(iterator); }

  UInt count(const Key &key) {
    Iterator begin = Base::find(key);
    return (begin != Base::end()) ? 1 : 0;
  }

  LWF::Range<Iterator> equalRange(const Key &key) const {
    Iterator lower = Base::lowerBound(key);
    return LWF::Range<Iterator>(lower, lower + 1);
  }

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}
};

}} // namespace High::Traits

namespace Low {
namespace Traits {

template <typename KBase, typename NBase, typename Size, typename Base>
struct Container : Base, Size {

  protected: struct Knot;
  protected: struct Node;
  protected: struct Multi;
  protected: struct Bound;
  protected: typedef typename Node::Branch Branch;
  public   : typedef typename Base::Key Key;
  public   : typedef typename Base::Type Type;
  public   : typedef typename Base::Comparer Comparer;
  public   : typedef typename Base::Allocator Allocator;
  public   : typedef typename Base::Insert Insert;
  public   : struct Iterator;

  Iterator begin() const { return Iterator(null.right(), null); }
  Iterator end  () const { return Iterator(null, null);   }
  Iterator top  () const { return Iterator(null.root(), null); }

  template <typename T>
  typename Insert::template Result<Iterator>
  insert(const Iterator &iterator, const T &value) {
    typename Branch::Ptr ptr = lookup(iterator, value);
    Branch& branch = *ptr;
    const Bool isNew = (Base::multi || branch == null);
    if (isNew) {
      branch = new (Base::allocator()) Node(value);
      branch->root() = ptr;
      branch->left() = (*branch).right() = null;
      null.update(ptr, branch);
      ++static_cast<Size &>(*this);
    } else { /* *branch = value; */ } // Don't change an existed node

    return typename
        Insert::template Result<Iterator>(Iterator(branch, null), isNew);
  }

  Void erase(Iterator iterator) {

    typename Node::Deleter deleter(lookup(iterator)); iterator = deleter;
    Branch &node = iterator, child = iterator.child();

    node->rootToMe() = child; // child may be null
    if (child != null) child->root() = node->root();
  }

  Iterator find(const Key &key) const {
    Branch node = top(); typename Branch::Kind kind;
    while (node != null &&
           (kind = ((*node)(key, Base::comparer()))) != Branch::Root) {
      node = (*node)[kind];
    } return Iterator(node, null);
  }

  template <typename Key>
  Iterator lowerBound(const Key &key) const {
    return this->bound<typename Bound::Lower>(key);
  }

  template <typename Key>
  Iterator upperBound(const Key &key) const {
     return bound<typename Bound::Upper>(key);
  }

  Void swap(Container &container) {
    LWF::swap<Size>(*this, container);
    LWF::swap<Base>(*this, container);
    LWF::swap(null, container.null);
  }

  Void clear() { clear(top()); null.loop(); }

  Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) {}

  UInt maxSize() const { return Base::allocator().maxSize();  }

  protected: typename Node::Deleter lookup/*to erase*/(Iterator iterator) {
    while (Node::Sterling == iterator.kind()) {
      Type &value = *iterator; value = *--iterator;
    } return null.update(iterator),
             --static_cast<Size &>(*this),
             typename Node::Deleter(iterator, Base::allocator());
  }

  protected: typename Branch::Ptr
  lookup/*to insert by hint*/(const Iterator &iterator, const Type &value) const {
    // Consider the range [<hint> --- <range up to> --- <edge>]:
    typename Branch::Ptr ptr =
          typename Branch::Ptr(null, Branch::Root); {
      const Branch &hint = iterator;
      if(hint == null)   {                                                      // No hint
        //ptr = still is root;                                                    // ptr = root
      } else {                                                                  // Consider the hint
        typename Branch::Kind kind = (*hint)(value, Base::comparer());
        if (Branch::Root == kind) {                                               // Equal to hint
          ptr = typename Branch::Ptr(hint->root(), hint.kind());                    // Use the hint as the result
          if (!Base::multi) return ptr;
        } else {                                                                  // Not equal to hint, hence looking for an edge
          Branch edge = Iterator(hint, null).root(kind);
          if (edge == null) {                                                       // The edge is infinite
           ptr = typename Branch::Ptr(hint, kind);                                    // Use a hint to lookup
          } else {                                                                  // The edge is finite
            typename Branch::Kind edgeKind = (*edge)(value, Base::comparer());
            if (Branch::Root == edgeKind) {                                           // Equal to the edge
              ptr = typename Branch::Ptr(edge->root(), edge.kind());                    // Use the edge as the result
              if (!Base::multi) return ptr;
            } else {                                                                  // Not equal to the edge
              if (edgeKind == Branch::reverse(kind)) {                                  // Is up to the edge (in the range)
                ptr = typename Branch::Ptr(hint, kind);                                   // use hint
              } else {                                                                  // Is out of the edge
                //ptr = still is root;                                                    // ptr = root
              }
            }
          }
        }
      }
    }
    return lookup(value, ptr);
  }

  protected: typename Branch::Ptr
  lookup/*to insert*/(const Type &value, typename Branch::Ptr ptr) const {
    typename Branch::Kind kind;
    typename Multi::template Comparer<> comparer(Base::comparer());
    while (*ptr != null &&
           (kind = (*(*ptr))(value, comparer)) != Branch::Root) {
      ptr += kind;
    } return ptr;
  }

  protected: template <typename Branch::Kind kind>
  Void rotate(const Branch &node) {
    const typename Branch::Kind rkind = Branch::template Reverse<kind>::kind;
    const Branch child = node->template branch<rkind>();

    if (child != null) { Branch grandchild = child->template branch<kind>();

      child->root() = node->root();
      node->rootToMe() = child;

      node->root() = child;
      child->template branch<kind>() = node;

      node->template branch<Branch::template Reverse<kind>::kind>() = grandchild;
      if (grandchild != null) { grandchild->root() = node; }
    }
  }

  protected: Void rotate(typename Branch::Kind kind, const Branch &node) {
    typename Branch::Kind rkind = Branch::reverse(kind);
    const Branch child = (*node)[rkind];

    if (child != null) { Branch grandchild = (*child)[kind];

      child->root() = node->root();
      node->rootToMe() = child;

      node->root() = child;
      (*child)[kind] = node;

      (*node)[rkind] = grandchild;
      if (grandchild != null) { grandchild->root() = node; }
    }
  }

  protected: Void clear(const Branch &node) {
    if (node != null) {
      --static_cast<Size &>(*this);
      typename Node::Deleter deleter(Iterator(node, null), Base::allocator());
      clear(node->left());
      clear(node->right());
    }
  }

  protected: template <typename Bound, typename Key>
  Iterator bound(const Key &key, const Bound &condition = Bound()) const {
    Branch node = top(), last = null; typename Branch::Kind kind;
    while (node != null) {
      if ((kind = condition((*node)(key, Base::comparer()))) == Branch::Left) {
        last = node;
      } node = (*node)[kind];
    } return Iterator(last, null);
  }

  protected: struct Multi {
    template <Bool = Base::multi, typename = Void> struct Comparer;
  };

  protected: struct Bound {
    struct Lower {
      typename Branch::Kind operator()(typename Branch::Kind kind) const {
        return kind == Branch::Right ? Branch::Right : Branch::Left;
      }
    };

    struct Upper {
      typename Branch::Kind operator()(typename Branch::Kind kind) const {
        return kind == Branch::Left ? Branch::Left: Branch::Right;
      }
    };
  };

  protected: struct Root; Root null;
};

template <typename Base, typename NBase, typename Size, typename CBase>
struct Container<Base, NBase, Size, CBase>::Knot : virtual Base {

  private: struct Named;
  public: struct Branch;

  enum Kind { Leaf = 0, Semiknot = 1, Sterling = 2 * Semiknot };

  Branch operator [] (typename Branch::Kind kind) const {
    return knot[kind - Branch::Left];
  }
  Branch &operator [] (typename Branch::Kind kind) {
    return knot[kind - Branch::Left];
  }
  template <typename Branch::Kind kind_>
  Branch &branch() { return knot[kind_ - Branch::Left]; }
  template <typename Branch::Kind kind_>
  Branch branch() const { return knot[kind_ - Branch::Left]; }

  Branch  left () const { return branch<Branch::Left >(); }
  Branch &left ()       { return branch<Branch::Left >(); }
  Branch  root () const { return branch<Branch::Root >(); }
  Branch &root ()       { return branch<Branch::Root >(); }
  Branch  right() const { return branch<Branch::Right>(); }
  Branch &right()       { return branch<Branch::Right>(); }

  Branch &rootToMe() {
    return root()->root () == *this ?  root()->root () :
           root()->left () == *this ?  root()->left () :
         /*root()->right() == *this ?*/root()->right() ;
  }

  operator Branch () const {
    return Branch(reinterpret_cast<Node *>(const_cast<Knot *>(this)));
  }

  Knot() {}
  ConstructionTransparency(Knot, Base) {}

  Void swap(Knot &knot) {
    LWF::swap(left (), knot.left ());
    LWF::swap(root (), knot.root ());
    LWF::swap(right(), knot.right());
  }

  private: Branch knot[Branch::Right - Branch::Left + 1];
};

template <typename KBase, typename NBase, typename Size, typename CBase>
struct Container<KBase, NBase, Size, CBase>::Knot::Branch : Weak::Ptr<Node[]> {
  private: typedef Weak::Ptr<Node[]> Base;
  public: enum Kind { Left = -1, Root = 0, Right = 1 };

  template <Kind kind_>
  struct Reverse {
    static const Kind kind = Kind(-kind_);
  };
  static Kind reverse(Kind kind) { return Kind(-kind); }

  struct Ptr  {
    Ptr (const Branch &root_, const Kind &kind_) : root(root_), kind(kind_) {}

    operator Kind() const { return kind; }
    Branch & operator * () const { return (*root)[kind]; }
    operator Branch () const { return root; }

    Ptr &operator += (const Kind &kind) {
      root = **this; this->kind = kind; return *this;
    }

    private: Branch root;
    private: Kind kind;
  };

  Branch(const LWF::Null & = LWF::null) : Base(LWF::null) {}
  Branch(const Base &base) : Base(base) {}
  Branch  &operator = (const Base &base) {
    Base::operator = (base); return *this;
  }

  Kind kind() const {
    Branch root = (*this)->root();
    return (root->right() == *this) ?  Right :
           (root->left () == *this) ?  Left  :
         /*(root->root () == *this) ?*/Root  ;
  }
};

template <typename KBase, typename Base, typename Size, typename CBase>
struct Container<KBase, Base, Size, CBase>::Node : Knot, virtual Base {

  struct Iterator;
  struct Deleter;

  template <typename Key, typename Comparer> typename Branch::Kind
  operator() (const Key &key, const Comparer& comparer) const {
    Int result = comparer(key, static_cast<const Type &>(*this));
    return result < 0 ? Branch::Left  :
           result > 0 ? Branch::Right :
         /*result == 0*/Branch::Root  ;
  }

  ConstructionTransparency(Node, Base) {}
};

template <typename KBase, typename NBase, typename Size, typename CBase>
struct Container<KBase, NBase, Size, CBase>::Node::Iterator : Branch {

  typedef Container::Type Type;
  struct Unbiased { typedef typename Iterator::Type Type; };
  struct Return { typedef typename Iterator::Type &Type; };

  Type &operator * () const { return *static_cast<const Branch &>(*this); }

  Int operator - (const Iterator &begin) const {
    Int distance = 0;
    for (Iterator end = *this; end != begin; --end) { ++distance; }
    return distance;
  }

  Iterator operator + (Int index) const {
    Iterator iterator = *this;
    if (index > 0) { for (;index != 0; --index) { ++iterator; }
    } else/* <= 0*/{ for (;index != 0; ++index) { --iterator; } }
    return iterator;
  }

  Type &operator [] (Int index) const { return *(*this + index); }

  Iterator(const Branch &branch, const Branch &null_)
    : Node::Branch(branch), null(null_) {}
  Iterator() {}

  typename Node::Kind kind() const { return typename
        Node::Kind(((*this)->left () != null ? Node::Semiknot : Node::Leaf) +
                   ((*this)->right() != null ? Node::Semiknot : Node::Leaf));
  }

  Branch child() const {
    return (*this)->left() != null ? (*this)->left() : (*this)->right();
  }

  Branch root(typename Branch::Kind kind) const {
    Branch last = *this, next = last->root();
    while (next != null && (*next)[kind] == last) {
      next = (last = next)->root();
    } return next;
  }

  template <typename Branch::Kind kind_>
  Branch root() const {
   Branch last = *this, next = last->root();
    while (next != null && next->template branch<kind_>() == last) {
      next = (last = next)->root();
    } return next;
  }

  template <typename Branch::Kind kind_>
  Branch most() const {
    Branch next = *this;
    while(next->template branch<kind_>() != null) {
      next = next->template branch<kind_>();
    } return next;
  }

  protected: Void operator ++ () { shift<Branch::Right>(); }
  protected: Void operator -- () { shift<Branch::Left >(); }
  protected: template <typename Branch::Kind kind_>
  Void shift() {
    Branch down = (*this)->template branch<kind_>();
    Branch::operator = ((null == down) ?
      root<kind_>() : Iterator(down, null). template
                          most<Branch::template Reverse<kind_>::kind>());
  }

  private: Branch null;
};

template <typename KBase, typename NBase, typename Size, typename CBase>
struct Container<KBase, NBase, Size, CBase>::Node::Deleter :
    Container::Iterator,
    LWF::Unique::Ptr<Node,
            LWF::Destroying::Deleter<Node, Container::Allocator> >  {

  typedef LWF::Unique::Ptr<Node, LWF::Destroying::Deleter<
              Node, Container::Allocator> > Base;

  Deleter(const Container::Iterator& iterator, const Container::Allocator &allocator)
    : Container::Iterator(iterator),
      Base(&*static_cast<const Branch &>(iterator), allocator) {}

  Deleter(const Deleter &deleter)
    : Container::Iterator(deleter),
      Base(const_cast<Base &>(static_cast<Base &>(*this))) { }
  Deleter &operator = (const Deleter &deleter) {
    Container::Iterator::operator = (deleter);
    Base::operator = (const_cast<Base &>(static_cast<Base &>(*this)));
    return *this;
  }
  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Deleter(Deleter &&deleter)
    : Container::Iterator(LWF::Forward::reference<Container::Iterator>(deleter)),
      Base(LWF::Forward::reference<Base>(deleter)) { }
  Deleter &operator = (Deleter &&deleter) {
    Container::Iterator::operator = (LWF::Forward::reference<Container::Iterator>(deleter));
    Base::operator = (LWF::Forward::reference<Base>(deleter));
    return *this;
  }
  #endif // C++11
};

template <typename KBase, typename NBase, typename Size, typename CBase>
struct Container<KBase, NBase, Size, CBase>::Root : Knot {

  Root() { loop(); }

  Void loop() { this->left() = this->root() = this->right() = (*this); }

  Void update/*while erase*/(const typename Container::Iterator &iterator) {
    const Branch &node = iterator;
    if (this->left () == node) { this->left () = iterator - 1; }
    if (this->right() == node) { this->right() = iterator + 1; }
  }

  Void update/*while insert*/(const typename Branch::Ptr &ptr,
                              const Branch &node) {
    typename Branch::Kind kind = ptr;
    if (this->left () == ptr && kind != Branch::Left ) { this->left () = node; }
    if (this->right() == ptr && kind != Branch::Right) { this->right() = node; }
  }

  Void swap(Root &root) {
    if (True/*Virtual Null*/) {
      this->swap(this->root(), root );
      root. swap(root .root(), *this);
    }{
      Branch &rt    = this->root()->root ();
      Branch &left  = this->right()->left();
      Branch &right = this->left()->right();
      rt = left = right = root;
    }{
      Branch &rt    = root. root()->root ();
      Branch &left  = root. right()->left();
      Branch &right = root. left()->right();
      rt = left = right = *this;
    }
    LWF::swap<Knot>(*this, root);
  }

  private: Void swap(const Branch &node, const Branch &null) {
    if (node != *this) {
      if(node->left () != *this) { this->swap(node->left (), null);
      } else { node->left () = null; }
      if(node->right() != *this) { this->swap(node->right(), null);
      } else { node->right() = null; }
    }
  }
};

template <typename KBase, typename NBase, typename Size, typename CBase>
struct Container<KBase, NBase, Size, CBase>::Iterator : LWF::Ptr<typename Node::Iterator> {
  protected: typedef LWF::Ptr<typename Node::Iterator> Base;
  public: Iterator() {}
  Iterator(const Branch &branch,
           const Branch &null) : Base(branch, null) {}
  WeaknessTransparency(Iterator, Base) {}
};

template <typename KBase, typename NBase, typename Size, typename CBase>
template <Bool multi, typename U>
struct Container<KBase, NBase, Size, CBase>::Multi::Comparer: Container::Comparer {
  Comparer(const Container::Comparer &base) : Container::Comparer(base) {}
  Int operator()(const typename Container::Key &a,
                 const typename Container::Key &b) const {
    const typename Container::Comparer &comparer = *this;
    Int result = comparer(a, b);
    return result >= 0 ? 1 : -1;
  }
};

template <typename KBase, typename NBase, typename Size, typename CBase>
template <typename U>
struct Container<KBase, NBase, Size, CBase>::Multi::Comparer<False, U>
                                 : Container::Comparer {
  Comparer(const Container::Comparer &base) : Container::Comparer(base) {}
};

}} // namespace Low::Tratis

struct Knot {};

template <typename Type>
struct Node : virtual LWF::Collection::Binary::Search::Tree::Knot {

  typename LWF::Collection::Binary::Search::Tree::Knot Knot;

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

template <typename Key>
struct Comparer {
  Int operator()(const Key &a, const Key &b) const { return a - b; }
};

template <typename Type>
struct Allocator: LWF::Std::Allocator {
  Bool operator == (const Allocator &) { return True; }
  UInt maxSize() const {
    return (LWF::Type<UInt32>::max - LWF::Type<UInt8>::max) /
            LWF::Type<Type>::size;
  }
};

}}}}}} // namespace CShift::LWF::Collection::Binary::Search::Tree


namespace CShift {
namespace LWF {
namespace Binary {
namespace Search {

template <
  typename Type,
  Bool     multi      = False,
  typename Key        = Type,
  typename Comparer   = LWF::Collection::Binary::Search::Tree::Comparer<Key>,
  typename Allocator  = LWF::Collection::Binary::Search::Tree::Allocator<Type>,
  Bool     countable  = False>
struct Tree
  : LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::Binary::Search::Tree::High::Traits::Container<
    LWF::Collection::Binary::Search::Tree::Low::Traits::Container<
      LWF::Collection::Binary::Search::Tree::Knot,
      LWF::Collection::Binary::Search::Tree::Node<Type>,
      LWF::Traits::Countable::Size<countable>,
      LWF::Collection::Associative::Container<
        Type, Key, Comparer, multi, Allocator> > > > >
{
  private: typedef
    LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::Binary::Search::Tree::High::Traits::Container<
    LWF::Collection::Binary::Search::Tree::Low::Traits::Container<
      LWF::Collection::Binary::Search::Tree::Knot,
      LWF::Collection::Binary::Search::Tree::Node<Type>,
      LWF::Traits::Countable::Size<countable>,
      LWF::Collection::Associative::Container<
        Type, Key, Comparer, multi, Allocator> > > > > Base;
  public:

  Tree(const Comparer &comparer = Comparer(),
       const Allocator &allocator = Allocator())
    : Base(comparer, allocator) {}

  template <typename Iterator>
  Tree(const Iterator &first, const Iterator &last,
       const Comparer &comparer = Comparer(),
       const Allocator &allocator = Allocator())
    : Base(first, last, comparer, allocator) { }

  template <typename Range>
  Tree(const Range &range,
       const Comparer &comparer = Comparer(),
       const Allocator &allocator = Allocator())
    : Base(range, comparer, allocator) {}
  template <typename Range>
  Tree &operator = (const Range &range) {
    Base::operator = (range); return *this;
  }

  #if PLATFORM_COMPILER_INITIALIZER_LIST
  Tree(const LWF::Initializer::List<Type> &list,
       const Comparer &comparer = Comparer(),
       const Allocator &allocator = Allocator())
    : Base(list, comparer, allocator) {}
  Tree &operator = (const LWF::Initializer::List<Type> &list) {
    Base::operator = (list); return *this;
  }
  #endif

  Tree (const Tree &tree,
        const Comparer &comparer = Comparer(),
        const Allocator &allocator = Allocator())
    : Base(tree, comparer, allocator) {}
  Tree &operator = (const Tree &tree) {
    Base::operator = (tree); return *this;
  }

  #if PLATFORM_COMPILER_RVALUE_REFERENCE
  Tree(Tree &&tree) : Base(LWF::Forward::reference<Base>(tree)) {}
  Tree &operator = (Tree &&tree) {
    Base::operator = (tree); return *this;
  }
  #endif // C++11
};

}}}} // namespace CShift::LWF::Binary::Search::Tree

#endif // CSHIFT_LWF_BINARY_SEARCH_TREE_H
