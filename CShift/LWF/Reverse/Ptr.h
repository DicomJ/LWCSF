#ifndef CSHIFT_LWF_REVERSE_PTR_H
#define CSHIFT_LWF_REVERSE_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace LWF {
namespace Reverse {

template<typename T> class Is;
template <typename Kind, Bool = LWF::Reverse::Is<Kind>::reverse> struct Unreversed;
template <typename Kind, Bool = LWF::Reverse::Is<Kind>::reverse> struct Reducted;

namespace Traits {

template <typename Base>
struct Ptr {
  typedef typename Base::Type Type;
  struct Unbiased { typedef typename Base::Unbiased::Type Type; };
  struct Return { typedef typename Base::Return::Type Type; };
  static const Bool weakness = Base::weakness;
  struct Reverse { typedef Base Basis; };

  typename Return::Type operator * () const { return *base; }

  private: struct Complement { Base base; };
  private: Ptr(const Complement &ptr) : base (ptr.base) {} public:
  Ptr operator + (Int index) const { Complement ptr = { base - index }; return ptr; }

  Int operator - (const Ptr &ptr) const { return ptr.base - base; }
  typename Return::Type operator [] (Int index) const { return base[-index]; }

  operator Base () const { Base base = this->base + 1; return base; }
  operator Base () { Base base = this->base + 1; return base; }

  Ptr(const Null & = null) { *this = null; }
  Ptr &operator = (const Null &) { return *this = Base(); }
  Bool operator == (const Null &) const { return *this == Ptr(null); }

  Ptr(const Ptr& ptr) : base(ptr.base) {}
  Ptr &operator = (const Ptr& ptr) { base = ptr.base; return *this; }
  Bool operator == (const Ptr &ptr) const { return base == ptr.base; }

  Ptr(const Base &base_) : base(base_ - 1) { }
  Ptr &operator = (const Base &base) { this->base = base - 1; return *this; }
  //Bool operator == (const Base &base) const { return *this == Ptr(base); }
  Bool operator == (const Type *ptr) const { return *this == Ptr((Type *)ptr); }

  template <typename U>
  operator const Ptr<U> &() const {
   return cast<U>(0);
  }
  private: template <typename U> const Ptr<U> &
  cast(typename U::Caster *) const {
    LWF::Traits::Lame(static_cast<const typename U::Caster &>(base));
    return *(const Ptr<U> *)this;
  }
  private: template <typename U> const Ptr<U> &
  cast(...) const {
   return *(const Ptr<U> *)this;
  }

#if 1
  private: class Deep {
    template <typename Basis = Base, Bool = LWF::Reverse::Is<Basis>::reverse>
    struct Traits { typedef Ptr Type; };

    template <typename Basis>
    struct Traits<Basis, False> { struct Type {}; };

    public: typedef LWF::Reverse::Unreversed<typename Traits<>::Type> Unreversed;
  };

  public: operator typename Deep::Unreversed::Type () {
    return Deep::Unreversed::type(*this);
  }
  public: operator typename Deep::Unreversed::Type () const {
    return Deep::Unreversed::type(*this);
  }
#endif
  private: Base base;
};

} // namespace Traits

template <typename Traits,
          typename Base_ = LWF::Ptr<
                           LWF::Reverse::Traits::Ptr<
                           typename LWF::Weak::Cast<Traits>::Range::Ptr> > >
struct Ptr : public Base_ {
  private: typedef Base_ Base; public:
  Ptr() {}
  PtrConstructionTransparency() {}
  WeaknessTransparency(Ptr, Base) {}
};


template <typename Ptr>
LWF::Reverse::Ptr<Ptr> ptr(const Ptr &ptr) { return ptr; }


template<typename T>
class Is {
  template<typename U> static LWF::Traits::Is    &criterion(typename U::Reverse::Basis *);
  template<typename  > static LWF::Traits::Isnot &criterion(...);
  public: static const bool reverse = sizeof(criterion<T>(0)) == sizeof(LWF::Traits::Is);
};

template <typename Kind, Bool reverse>
struct Unreversed {
  typedef typename Unreversed<typename Kind::Reverse::Basis>::Type Type;
  static Type type(const Kind &ptr) {
    typedef typename Kind::Reverse::Basis Base; Base p = ptr;
    return Unreversed<Base>::type(p);
  }
};

template <typename Kind>
struct Unreversed <Kind, False > {
  typedef Kind Type;
  static const Type &type(const Kind &ptr) { return ptr; }
};

template <typename Ptr>
typename LWF::Reverse::Unreversed<Ptr>::Type unreversed(const Ptr &ptr) {
  return Unreversed<Ptr>::type(ptr);
}

template <typename Kind, Bool reverse>
struct Reducted {
  template <typename Basis = typename Kind::Reverse::Basis,
            Bool = LWF::Reverse::Is<Basis>::reverse> struct Fraction {
    typedef typename Reducted<typename Basis::Reverse::Basis>::Type Type;
    static const Type type(const Kind& ptr__) {
      Basis ptr_ = ptr__; typename Basis::Reverse::Basis ptr = ptr_;
      return Reducted<typename Basis::Reverse::Basis>::type((ptr));
    }
  };
  template <typename Basis> struct Fraction<Basis, False> {
    typedef Kind Type;
    static const Type &type(const Kind& ptr) { return ptr; }
  };
  typedef typename Fraction<>::Type Type;

  static Type type(const Kind& ptr) { return Fraction<>::type(ptr); }
};
template <typename Kind>
struct Reducted<Kind, False> {
  typedef Kind Type;
  static const Type &type(const Kind& ptr) { return ptr; }
};

template <typename Ptr>
typename LWF::Reverse::Reducted<Ptr>::Type reducted(const Ptr &ptr) {
  return Reducted<Ptr>::type(ptr);
}

}}} // namespace CShift::LWF::Reverse

#endif // CSHIFT_LWF_REVERSE_PTR_H
