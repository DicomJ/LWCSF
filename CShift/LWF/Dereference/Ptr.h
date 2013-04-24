#ifndef CSHIFT_LWF_DEREFERENCE_PTR_H
#define CSHIFT_LWF_DEREFERENCE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Ptr.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {
namespace Dereference {

namespace Traits {

template <typename Base_>
struct Ptr : Base_ {
  private: typedef Base_ Base; public:
  public : typedef typename Base::Type Subbase;
  public : typedef typename Subbase::Type Type;
  struct Return {
    typedef typename LWF::Traits::Uvalue::Ptr<Subbase, typename Ptr::Type>::Return::Type Type;
  };

  typename Return::Type operator * () const { return * Base::operator * (); }

  Ptr() {}
  PtrConstructionTransparency() {}
};

} // namespace Traits

template <typename Traits>
struct Ptr : public LWF::Ptr<LWF::Dereference::Traits::Ptr<
                             typename LWF::Weak::Cast<Traits>::Ptr> > {
  private: typedef
    LWF::Ptr<LWF::Dereference::Traits::Ptr<
             typename LWF::Weak::Cast<Traits>::Ptr> > Base;
  public:

  Ptr() {}
  PtrConstructionTransparency() {}
};


template <typename Ptr>
LWF::Dereference::Ptr<Ptr> ptr(const Ptr &ptr) { return ptr; }

}}} // namespace CShift::LWF::Dereference

#endif // CSHIFT_LWF_DEREFERENCE_PTR_H
