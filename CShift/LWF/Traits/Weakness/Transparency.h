#ifndef CSHIFT_LWF_TRAITS_WEAKNESS_TRANSPARENCY_H
#define CSHIFT_LWF_TRAITS_WEAKNESS_TRANSPARENCY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Traits {

#define ExplictWeaknessTransparency(Class, Base) \
  \
  Class operator + (Int index) const { return Base::operator + (index); }\
  Class operator - (Int index) const { return Base::operator - (index); }\
  \
  Class& operator += (Int index) { return Base::operator += (index), *this; }\
  Class& operator -= (Int index) { return Base::operator -= (index), *this; }\
  \
  Class& operator ++ () { return Base::operator ++(), *this; }\
  Class& operator -- () { return Base::operator --(), *this; }\
  \
  Class operator ++ (Int32) { return Base::operator ++ (Int32(1)); }\
  Class operator -- (Int32) { return Base::operator -- (Int32(1)); }\
  \
  Int operator - (const Class &base) const { return Base::operator - (base); }\
  \
  public:  inline Void Class##ExplictWeaknessTransparency()

#define WeaknessTransparency(Class, Base) \
  ExplictWeaknessTransparency(Class, Base) {} \
  private: Class(const Base &base) : Base(base) {} \
  private: Class &operator = (const Base &base) { Base::operator = (base); return *this; } \
  public:  inline Void Class##WeaknessTransparency()

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_WEAKNESS_TRANSPARENCY_H
