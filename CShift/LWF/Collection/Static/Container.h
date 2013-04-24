#ifndef CSHIFT_LWF_COLLECTION_STATIC_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_STATIC_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Collection/Static/Forward/Container.h"
#include "LWF/Reverse/Ptr.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Static {

template <typename Traits>
struct Container : LWF::Collection::Static::Forward::Container<Traits> {

  private: typedef LWF::Collection::Static::Forward::Container<Traits> Base;
  private: template <typename T> struct Is;
  public: typedef typename Base::Iterator Iterator;
  public: typedef typename Iterator::Type Type;
  public: struct Reverse {
    typedef LWF::Reverse::Ptr<typename Container::Iterator>          Iterator;
  }; public: struct Const {
    typedef LWF::Const::Ptr<typename Container::Iterator>            Iterator;
    struct Reverse {
      typedef LWF::Const::Ptr<typename Container::Reverse::Iterator> Iterator;
    };
  };

  typename        Reverse::Iterator  rbegin()       { return Base::end  (); }
  typename        Reverse::Iterator  rend  ()       { return Base::begin(); }
  typename Const::Reverse::Iterator  rbegin() const { return     crbegin(); }
  typename Const::Reverse::Iterator  rend  () const { return     crend  (); }
  typename Const::Reverse::Iterator crbegin() const { return Base::end  (); }
  typename Const::Reverse::Iterator crend  () const { return Base::begin(); }

  typename        Iterator::Return::Type back ()       { return * rbegin(); }
  typename Const::Iterator::Return::Type back () const { return *crbegin(); }

  ConstructionTransparency(Container, Base) {}
};

}}}} // namespace CShift::LWF::Collection::Static

#endif // CSHIFT_LWF_COLLECTION_STATIC_CONTAINER_H
