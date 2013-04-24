#ifndef CSHIFT_TEXT_CSTRING_H
#define CSHIFT_TEXT_CSTRING_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Weak/Ptr.h"


namespace CShift {
namespace Text {

template <typename Type>
struct CString : LWF::Weak::Ptr<Type[]>  {
  private: typedef LWF::Weak::Ptr<Type[]> Base; public:

  typedef LWF::Range<Base> Range;

  UInt size() const {
    UInt i = 0; while ((*this)[i] != Type(0)) { ++i; } return i;
  }

  Range range(UInt count) const {
    return LWF::range(static_cast<const Base &>(*this), *this + count);
  }

  Range range() const { return range(size()); }

  CString(Type *ptr) : Base(ptr) {}

  CString(const Null &ptr = null) : Base(ptr) {}
  CString &operator = (const Null &ptr) { Base::operator = (ptr); return *this; }

  CString(const CString &ptr) : Base(ptr) {}
  CString &operator = (const CString &ptr) { Base::operator = (ptr); return *this; }
};

template <typename Type>
Text::CString<Type> cstring(Type *cstr) { return cstr; }

}} // namespace CShift::Text

#endif // CSHIFT_TEXT_CSTRING_H
