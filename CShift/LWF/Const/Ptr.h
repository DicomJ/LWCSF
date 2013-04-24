#ifndef CSHIFT_LWF_CONST_PTR_H
#define CSHIFT_LWF_CONST_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {
namespace Const {

namespace Traits {

template <typename Base_>
struct Ptr : public Base_ {
  private: typedef Base_ Base;
  public:
  typedef const typename Base::Type Type;
  struct Return {
    typedef typename LWF::Traits::Uvalue::Ptr<Base, typename Ptr::Type>::Return::Type Type;
  };

  Ptr() {}
  PtrConstructionTransparency() {}

  Ptr(Type *ptr) : Base(const_cast<typename Base::Type *>(ptr)) {}

  template <typename U> Ptr(Type *ptr, const U &u)
    : Base(const_cast<typename Base::Type *>(ptr), u) {}
  template <typename U> Ptr(Type *ptr, U &u)
    : Base(const_cast<typename Base::Type *>(ptr), u) {}

  template <typename U, typename UU> Ptr(Type *ptr, const U &u, const UU &uu)
    : Base(const_cast<typename Base::Type *>(ptr), u, uu) {}
  template <typename U, typename UU> Ptr(Type *ptr, U &u, const UU &uu)
    : Base(const_cast<typename Base::Type *>(ptr), u, uu) {}
  template <typename U, typename UU> Ptr(Type *ptr, const U &u,UU &uu)
    : Base(const_cast<typename Base::Type *>(ptr), u, uu) {}
  template <typename U, typename UU> Ptr(Type *ptr, U &u,UU &uu)
    : Base(const_cast<typename Base::Type *>(ptr), u, uu) {}
};

} // namespace Traits

template <typename Traits,
          typename Base_ = LWF::Ptr<
                          LWF::Const::Traits::Ptr<
                          typename LWF::Weak::Cast<Traits>::Ptr> >,
          Bool = Base_::weakness>
struct Ptr : public Base_ {
  private: typedef Base_ Base; public:
  Ptr() {}
  PtrConstructionTransparency() {}
  WeaknessTransparency(Ptr, Base) {}
};

template <typename Traits, typename Base_>
struct Ptr<Traits, Base_, False> : public Base_ {
  private: typedef Base_ Base; public:
  Ptr() {}
  PtrConstructionTransparency() {}
};

template <typename Ptr>
LWF::Const::Ptr<Ptr> ptr(const Ptr &ptr) { return ptr; }

}}} // namespace CShift::LWF::Const

#endif // CSHIFT_LWF_CONST_PTR_H
