#ifndef CSHIFT_LWF_REFERENCE_PTR_H
#define CSHIFT_LWF_REFERENCE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Intrusive/Ptr.h"
#include "LWF/Reference/Interface.h"


namespace CShift {
namespace LWF {
namespace Reference {

namespace Traits {

template <typename T>
struct Adjuster : T
{
  inline Void operator ++() { this->IncRef(); }
  inline Void operator --() { this->DecRef(); }

  private: inline Void IncRef() {}
  private: inline Void DecRef() {}
};

} // namespace Traits

template <typename Traits>
struct Ptr: LWF::Intrusive::Ptr<Traits,
                            LWF::Reference::Traits::Adjuster<Traits> > {
  
  private: typedef
    LWF::Intrusive::Ptr<Traits, LWF::Reference::Traits::Adjuster<Traits> > Base;
  public: typedef
    typename Base::Type Type;

  Ptr(Type *ptr) : Base(ptr) {}

  Ptr(const Null &ptr = null) : Base(ptr) {}
  Ptr &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  Ptr(const Ptr &ptr) : Base(ptr) {}
  Ptr &operator = (const Ptr &ptr) { Base::operator = (ptr); return *this; }

  template <typename U>
  Ptr(const Ptr<U> &ptr) : Base(ptr) {}

  template <typename U>
  Ptr &operator = (const Ptr<U> &ptr) {
    Base::operator = (static_cast<const Base &>(ptr)); return *this;
  }
};

}}} // namespace CShift::LWF::Reference

#endif // CSHIFT_LWF_REFERENCE_PTR_H
