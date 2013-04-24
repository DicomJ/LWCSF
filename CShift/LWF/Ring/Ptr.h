#ifndef CSHIFT_LWF_RING_PTR_H
#define CSHIFT_LWF_RING_PTR_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"
#include "LWF/Range.h"
#include "LWF/Algorithm/absolute.h"
#include "LWF/Traits/Prediction.h"


namespace CShift {
namespace LWF {
namespace Ring {

namespace Traits {

template <typename Base_>
struct Ptr : Base_ {
  protected: typedef Base_ Base; public:

  LWF::Range<Base> range() const { return LWF::Range<Base>(range_, range_.size); }

  protected: struct Range : Base_ { UInt size;
    Range(const Base_ &base, UInt size_)
      : Base_(base), size(size_ != 0 ? size_ : 1) {}

    Range(const Range &range)
      : Base_(static_cast<const Base_ &>(range)), size(range.size) {}
    Range &operator = (const Range &range) {
      Base_::operator = (static_cast<const Base_ &>(range));
      size = range.size;
      return *this;
    }

    Range(const Null & = null) : size(1) {}
    Range &operator = (const Null &) {
      Base::operator = (Base()); size = 1; return *this;
    }
  };

  UInt index() const { return static_cast<const Base &>(*this) - range_; }

  Ptr operator + (Int index) const {
    return Ptr(range_ + (this->index() + abs(index)) % range_.size,
               range_, range_.size, absolute + index);
  }

  template <typename U>
  Bool operator == (const U &u) const { return equal(u); }

  Int operator - (const Ptr &ptr) const {
    return absolute - ptr.absolute;
  }

  typename Base::Return::Type operator [] (Int index) const {
    return *(*this + index);
  }

  Ptr(const Null & = null) : range_(null), absolute(0) {}
  Ptr &operator = (const Null &) {
    static_cast<Base &>(*this) = Base(); range_ = null; absolute = 0;
    return *this;
  }
  Ptr(const Base &base, const Base &begin_, UInt size)
    : Base(base), range_(begin_, size), absolute(base - begin_) {}
  Ptr(const Base &base, const Base &begin_, UInt size, Int absolute_)
    : Base(base), range_(begin_, size), absolute(absolute_) {}
  public: Ptr(const Ptr &ptr)
    : Base(static_cast<const Base &>(ptr)), range_(ptr.range_),
      absolute(ptr.absolute) {}

  private: Int abs(Int index) const {
    return (index > 0 ? index: LWF::absolute(index + Int(range_.size)));
  }

  private: template <typename U>
  Bool equal(const U &u,
             typename LWF::Traits::Prediction<!LWF::Type<U>::Is::Castable::template To<Ptr>::type>::Type * = 0) const {
    return Base::operator == (u);
  }

  private: template <typename U>
  Bool equal(const U &u,
             typename LWF::Traits::Prediction<LWF::Type<U>::Is::Castable::template To<Ptr>::type>::Type * = 0) const {
    const Ptr &ptr = static_cast<const Ptr &>(u);
    return range_ + absolute == ptr.range_ + ptr.absolute;
  }

  private: Range range_;
  private: Int absolute;
};

} // namespace Traits

template <typename Traits>
struct Ptr
  : LWF::Ptr<LWF::Ring::Traits::Ptr<typename LWF::Weak::Cast<Traits>::Ptr> >
{
  private: typedef
    LWF::Ptr<LWF::Ring::Traits::Ptr<typename LWF::Weak::Cast<Traits>::Ptr> > Base;
  public:

  Ptr(const typename LWF::Weak::Cast<Traits>::Ptr &base = null,
      const typename LWF::Weak::Cast<Traits>::Ptr &begin = null, UInt size = 0)
    : Base(base, begin, size) {}
  PtrConstructionTransparency() {}
  WeaknessTransparency(Ptr, Base) {}
};

template <typename Ptr>
LWF::Ring::Ptr<Ptr> ptr(const Ptr &ptr, const Ptr &begin, UInt size) {
  return LWF::Ring::Ptr<Ptr>(ptr, begin, size);
}

template <typename Ptr>
LWF::Ring::Ptr<Ptr> ptr(const Ptr &ptr, const Ptr &begin, const Ptr &end) {
  return LWF::Ring::ptr(ptr, begin, UInt(end - begin));
}

template <typename Ptr>
LWF::Ring::Ptr<Ptr> ptr(const Ptr &ptr, const LWF::Range<Ptr> &range) {
  return LWF::Ring::ptr(ptr, range.begin, range.size());
}

}}} // namespace CShift::LWF::Ring

#endif // CSHIFT_LWF_RING_PTR_H
