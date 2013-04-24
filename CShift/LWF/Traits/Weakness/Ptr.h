#ifndef CSHIFT_LWF_TRAITS_WEAKNESS_PTR_H
#define CSHIFT_LWF_TRAITS_WEAKNESS_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"
#include "LWF/Traits/Prototype.h"
#include "LWF/Traits/Weakness/Transparency.h"
#include "LWF/Traits/Ptr.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Weakness {

template <typename Base,
          Bool subscriptible =
                 LWF::Type<typename Base::Unbiased::Type>::subscriptible>
struct Ptr;

template <typename Base_>
struct Ptr<Base_, False> : Base_ {
  private: typedef Base_ Base; public:
  static const Bool weakness = False;

  PtrConstructionTransparency() {}

  private: Int operator - (const Ptr &ptr) const;
  private: Ptr operator + (Int index) const;
  private: typename Base::Type & operator [] (Int index) const;
};

template <typename Base_>
struct Ptr<Base_, True> : Base_ {
  private: typedef Base_ Base; public:
  static const Bool weakness = True;

  PtrConstructionTransparency() {}

  Int operator - (const Ptr &ptr) const { return &**this - &*ptr; }
  Ptr operator + (Int index) const { return Ptr(&**this + index); }
  typename Base::Type & operator [] (Int index) const { return *(&**this + index); }
};

}}}} // namespace CShift::LWF::Traits::Weakness

#endif // CSHIFT_LWF_TRAITS_WEAKNESS_PTR_H
