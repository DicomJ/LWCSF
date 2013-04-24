#ifndef CSHIFT_LWF_TRAITS_CONSTRUCTION_TRANSPARENCY_H
#define CSHIFT_LWF_TRAITS_CONSTRUCTION_TRANSPARENCY_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Forward/reference.h"


namespace CShift {
namespace LWF {
namespace Traits {

#if PLATFORM_COMPILER_RVALUE_REFERENCE
#define ConstructionTransparency(Class, Base) \
  template <typename U>\
  Class &operator = (U &&u) {\
    Base::operator = (LWF::Forward::reference<U >(u)); return *this; }\
  \
  template <typename U>\
  Class(U &&u) : Base(LWF::Forward::reference<U>(u)) {}\
  \
  template <typename U, typename UU>\
  Class(U&&u, UU &&uu) : Base(LWF::Forward::reference<U >(u),\
                              LWF::Forward::reference<UU>(uu)) {}\
  \
  template <typename U, typename UU, typename UUU>\
  Class(U&&u, UU &&uu, UUU  &&uuu) : Base(LWF::Forward::reference<U>(u),\
                                          LWF::Forward::reference<UU>(uu),\
                                          LWF::Forward::reference<UUU>(uuu)) {}\
  \
  inline Void Class##ConstructionTransparency()
#else
#define ConstructionTransparency(Class, Base) \
  template <typename U>\
  Class &operator = (      U  &u) { Base::operator = (u); return *this; }\
  template <typename U>\
  Class &operator = (const U  &u) { Base::operator = (u); return *this; }\
  \
  template <typename U>\
  Class(      U &u) : Base(u) {}\
  template <typename U>\
  Class(const U &u) : Base(u) {}\
  \
  template <typename U, typename UU>\
  Class(      U  &u,       UU  &uu) : Base(u, uu) {}\
  template <typename U, typename UU>\
  Class(      U  &u, const UU  &uu) : Base(u, uu) {}\
  template <typename U, typename UU>\
  Class(const U  &u,       UU  &uu) : Base(u, uu) {}\
  template <typename U, typename UU>\
  Class(const U  &u, const UU  &uu) : Base(u, uu) {}\
  \
  template <typename U, typename UU, typename UUU>\
  Class(      U   &u,       UU  &uu,       UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(      U   &u,       UU  &uu, const UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(      U   &u, const UU  &uu,       UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(      U   &u, const UU  &uu, const UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(const U   &u,       UU  &uu,       UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(const U   &u,       UU  &uu, const UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(const U   &u, const UU  &uu,       UUU  &uuu) : Base(u, uu, uuu) {}\
  template <typename U, typename UU, typename UUU>\
  Class(const U   &u, const UU  &uu, const UUU  &uuu) : Base(u, uu, uuu) {}\
  \
  inline Void Class##ConstructionTransparency()
#endif // !C++11

}}} // namespace CShift::LWF::Traits
  
#endif // CSHIFT_LWF_TRAITS_CONSTRUCTION_TRANSPARENCY_H
