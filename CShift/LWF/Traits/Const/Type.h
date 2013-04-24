#ifndef CSHIFT_LWF_TRAITS_CONST_TYPE_H
#define CSHIFT_LWF_TRAITS_CONST_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Const {

template <typename T>
struct Type {
  static const Bool constant = LWF::Kind::Boolean::Traits<Bool>::False;
};

template <typename T>
struct Type <const T> {
  static const Bool constant = LWF::Kind::Boolean::Traits<Bool>::True;
};

}}}} // namespace CShift::LWF::Traits::Const

#endif // CSHIFT_LWF_TRAITS_CONST_TYPE_H
