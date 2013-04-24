#ifndef CSHIFT_LWF_COLLECTION_STATIC_FORWARD_CONTAINER_H
#define CSHIFT_LWF_COLLECTION_STATIC_FORWARD_CONTAINER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Const/Ptr.h"
#include "LWF/Traits/Prediction.h"
#include "LWF/Algorithm/Equal/Exactly.h"
#include "LWF/Algorithm/Different/Exactly.h"
#include "LWF/Traits/Countable/Size.h"


namespace CShift {
namespace LWF {
namespace Collection {
namespace Static {
namespace Forward {

template <typename Base>
struct Container : Base {

  private: template <typename T> struct Is;
  public: typedef typename Base::Iterator Iterator;
  public: typedef typename Iterator::Type Type;
  public: struct Const {
    typedef LWF::Const::Ptr<typename Container::Iterator> Iterator;
  };
                 Iterator   begin()       { return Base::begin(); }
                 Iterator   end  ()       { return Base::end  (); }
  typename Const::Iterator  begin() const { return      cbegin(); }
  typename Const::Iterator  end  () const { return      cend  (); }
  typename Const::Iterator cbegin() const { return Base::begin(); }
  typename Const::Iterator cend  () const { return Base::end  (); }

  typename        Iterator::Return::Type front()       { return *  begin(); }
  typename Const::Iterator::Return::Type front() const { return * cbegin(); }

  typename        Iterator::Return::Type         at(Int index)       { return  begin ()[index]; }
  typename Const::Iterator::Return::Type         at(Int index) const { return  cbegin()[index]; }
  typename        Iterator::Return::Type operator[](Int index)       { return        at(index); }
  typename Const::Iterator::Return::Type operator[](Int index) const { return        at(index); }

  UInt size () const { return size_<Container>();  }
  Bool empty() const { return empty_<Container>(); }

  template <typename U>
  Bool operator == (const U &u) const { return equal_(u); }
  template <typename U>
  Bool operator != (const U &u) const { return !(*this == u); }

  template <typename Range>
  Bool equal(const Range &range) const {
    return equal<LWF::Algorithm::Equal::Exactly, Range>(range);
  }
  template <typename How, typename Range>
  Bool equal(const Range &range, const How &how = How(),
             typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) const {
    return isThis(range) ? True : how(*this, range);
  }
  template <typename How, typename Iterator>
  Bool equal(const Iterator &begin, const Iterator &end, const How &how = How()) const {
    return how(*this, begin, end);
  }

  template <typename U>
  Int operator - (const U &u) const { return different_(u); }
  template <typename U>
  Bool operator >  (const U &u) const { return (*this - u) >  0; }
  template <typename U>
  Bool operator >= (const U &u) const { return (*this - u) >= 0; }
  template <typename U>
  Bool operator <  (const U &u) const { return (u > *this);      }
  template <typename U>
  Bool operator <= (const U &u) const { return (u >= *this);     }

  template <typename Range>
  Int different(const Range &range) const {
    return different<LWF::Algorithm::Different::Exactly, Range>(range);
  }
  template <typename How, typename Range>
  Int different(const Range &range, const How &how = How()) const {
    return isThis(range) ? 0 : how(*this, range);
  }
  template <typename How, typename Iterator>
  Int different(const Iterator &begin, const Iterator &end, const How &how = How()) const {
    return how(*this, begin, end);
  }

  ConstructionTransparency(Container, Base) {}

  protected: template <typename C> UInt
  size_(typename LWF::Traits::Prediction<Is<C>::countable>::Type * = 0) const {
     return static_cast<const LWF::Traits::Countable::Size<True> &>(*this).size();
  }
  protected: template <typename C> Bool
  empty_(typename LWF::Traits::Prediction<Is<C>::countable>::Type * = 0) const {
    return 0 == static_cast<const LWF::Traits::Countable::Size<True> &>(*this).size();
  }

  protected: template <typename C> UInt
  size_(typename LWF::Traits::Prediction<!Is<C>::countable>::Type * = 0) const {
    return end() - begin();
  }
  protected: template <typename C> Bool
  empty_(typename LWF::Traits::Prediction<!Is<C>::countable>::Type * = 0) const {
    return begin() == end();
  }

  protected: template <typename Range>
  Int isThis(const Range &range, typename LWF::Traits::Prediction<
             Is<Range>::container >::Type * = 0) const {
    return this == &range;
  }
  protected: template <typename Range>
  Int isThis(const Range &, typename LWF::Traits::Prediction<
             !Is<Range>::container >::Type * = 0) const {
    return False;
  }
  private: template <typename U>
  Bool equal_(const U &u,
              typename LWF::Traits::Prediction<!Is<U>::range>::Type * = 0) const {
    return Base::operator == (u);
  }
  private: template <typename Range>
  Bool equal_(const Range &range,
             typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) const {
    return equal(range);
  }
  private: template <typename U>
  Int different_(const U &u,
                 typename LWF::Traits::Prediction<!Is<U>::range>::Type * = 0) const {
    return Base::operator - (u);
  }
  private: template <typename Range>
  Int different_(const Range &range,
                 typename LWF::Traits::Prediction<Is<Range>::range>::Type * = 0) const {
    return different(range);
  }
};

template <typename Base>
template <typename T>
struct Container<Base>::Is {
  static const Bool range =
      LWF::Type<T>::Is::range;
  static const Bool container =
      LWF::Type<Container>::Is::Base::template Of<T>::type;
  static const Bool countable =
      LWF::Type<LWF::Traits::Countable::template Size<True> >::Is::Base::template Of<T>::type;
};

}}}}} // namespace CShift::LWF::Collection::Static::Forward

#endif // CSHIFT_LWF_COLLECTION_STATIC_FORWARD_CONTAINER_H
