#ifndef CSHIFT_LWF_BINARY_SEARCH_RED_BLACK_TREE_H
#define CSHIFT_LWF_BINARY_SEARCH_RED_BLACK_TREE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Binary/Search/Tree.h"


namespace CShift {
namespace LWF {

namespace Collection {
namespace Binary {
namespace Search {
namespace RB {
namespace Tree {

template <typename Base>
struct Container : Base {
  protected: typedef typename Base::Knot Knot;
  protected: typedef typename Base::Node Node;
  protected: typedef typename Base::Branch Branch;
  public   : typedef typename Base::Type Type;
  public   : typedef typename Base::Comparer Comparer;
  public   : typedef typename Base::Allocator Allocator;
  public   : typedef typename Base::Iterator Iterator;

  template <typename T>
  typename Base::Insert::template Result<Iterator>
  insert(const Iterator &iterator, const T &value) {
    typename Base::Insert::template Result<Iterator> result =
        Base::insert(iterator, value);

    if (result) {
      Branch node = static_cast<const Iterator &>(result);
      do {
        Branch parent = node->root();
        if (parent == Base::null) {
          node->color = Node::Black;
          node = Base::null;
        } else if (Node::Black == parent->color) {
          node = Base::null;
        } else {
          const typename Branch::Kind kind = parent.kind(),
                 rkind = Branch::reverse(kind);
          const Branch grandparent = parent->root();
          const Branch uncle = (*grandparent)[rkind];
          if (Node::Red == uncle->color) { // Recoloring
            parent->color = uncle->color = Node::Black;
            grandparent->color = Node::Red;
            node = grandparent; // do RECURSION
          } else { // Rotation
            if (node.kind() != kind) { rotate(kind, parent); parent = node; }
            parent->color = Node::Black;
            grandparent->color = Node::Red;
            rotate(rkind, grandparent);
            node = Base::null;
          }
        }
      } while (node != Base::null);
    }
    return result;
  }

  Void erase(Iterator iterator) {

    typename Node::Deleter deleter(Base::lookup(iterator)); iterator = deleter;
    Branch &node = iterator, child = iterator.child();
    Knot null(Node::Black);

    if (child == Base::null) { child = null; }

    node->rootToMe() = child;
    child->root() = node->root();

    if (Node::Black == node->color) {
      if (Node::Red == child->color) {
        child->color = Node::Black;
      } else {
        node = child;
        do {
          const Branch parent = node->root();
          if (parent == Base::null) {
            node = Base::null;
          } else {
            const typename Branch::Kind kind = node.kind(),
              rkind = Branch::reverse(kind);

            Branch sibling = (*parent)[rkind];
            if (Node::Red == sibling->color) {
              parent ->color = Node::Red;
              sibling->color = Node::Black;
              rotate(kind, parent);
              sibling = (*parent)[rkind];
            }
            if (Node::Black == sibling->color &&
                Node::Black == sibling->left()->color &&
                Node::Black == sibling->right()->color) { // Recoloring
              sibling->color = Node::Red;
              if (Node::Black == parent->color) {
                node = parent; // do RECURSION
              } else {
                parent->color = Node::Black;
                node = Base::null;
              }
            } else {  // Rotation
              if (Node::Black == sibling->color &&
                  Node::Red   == (*sibling)[ kind]->color &&
                  Node::Black == (*sibling)[rkind]->color) {
                sibling->         color = Node::Red;
                (*sibling)[kind]->color = Node::Black;
                rotate(rkind, sibling);
                sibling = (*parent)[rkind];
              }
              sibling->color           = parent->color;
              (*sibling)[rkind]->color =
              parent->           color = Node::Black;
              rotate(kind, parent);
              node = Base::null;
            }
          }
        } while (node != Base::null);
      }
    } if (null.root() != LWF::null) { null.rootToMe() = Base::null; }
  }

  template <typename Key>
  Iterator find(const Key &key) const {
    Iterator iterator = Base::lowerBound(key);
    return iterator != Base::end() && 0 == Base::comparer()(*iterator, key) ?
      iterator : Base::end();
  }

  protected: Container(const Comparer &comparer, const Allocator &allocator)
    : Base(comparer, allocator) { Base::null.color = Node::Black; }
};

struct Knot : virtual LWF::Collection::Binary::Search::Tree::Knot {
  enum Color { Red, Black } color;
  Knot(Color color_ = Red) : color(color_) {}
};

template <typename Type>
struct Node : virtual LWF::Collection::Binary::Search::RB::Tree::Knot,
              LWF::Collection::Binary::Search::Tree::Node<Type> {

  private: typedef LWF::Collection::Binary::Search::Tree::Node<Type> Base;
  public: ConstructionTransparency(Node, Base) {}
};

template <typename Key>
struct Comparer :
LWF::Collection::Binary::Search::Tree::Comparer<Key> {};

template <typename Type>
struct Allocator :
LWF::Collection::Binary::Search::Tree::Allocator<Type> {};

}}}}} // namespace Collection::Binary::Search::Red::Black::Tree

namespace Binary {
namespace Search {
namespace RB {

template <
  typename Type,
  Bool     multi      = False,
  typename Key        = Type,
  typename Comparer   = LWF::Collection::Binary::Search::RB::Tree::Comparer<Key>,
  typename Allocator  = LWF::Collection::Binary::Search::RB::Tree::Allocator<Type>,
  Bool     countable  = False>
struct Tree
  : LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::Binary::Search::Tree::High::Traits::Container<
    LWF::Collection::Binary::Search::RB::Tree::Container<
    LWF::Collection::Binary::Search::Tree::Low::Traits::Container<
      LWF::Collection::Binary::Search::RB::Tree::Knot,
      LWF::Collection::Binary::Search::RB::Tree::Node<Type>,
      LWF::Traits::Countable::Size<countable>,
      LWF::Collection::Associative::Container<
        Type, Key, Comparer, multi, Allocator> > > > > >
{
  private: typedef
    LWF::Collection::Associative::Dynamic::Container<
    LWF::Collection::Static::Container<
    LWF::Collection::Binary::Search::Tree::High::Traits::Container<
    LWF::Collection::Binary::Search::RB::Tree::Container<
    LWF::Collection::Binary::Search::Tree::Low::Traits::Container<
      LWF::Collection::Binary::Search::RB::Tree::Knot,
      LWF::Collection::Binary::Search::RB::Tree::Node<Type>,
      LWF::Traits::Countable::Size<countable>,
      LWF::Collection::Associative::Container<
        Type, Key, Comparer, multi, Allocator> > > > > > Base;
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

  Tree(const Tree &tree,
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

}}} // namespace Binary::Search::Red::Black

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_BINARY_SEARCH_RED_BLACK_TREE_H
