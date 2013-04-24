#ifndef CSHIFT_LWF_TRAITS_MATCH_TYPE_H
#define CSHIFT_LWF_TRAITS_MATCH_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Match {

template <typename T, typename AnotherT>
struct Type { static const Bool equal = LWF::Kind::Boolean::Traits<Bool>::False; };

template <typename T>
struct Type<T, T> { static const Bool equal = LWF::Kind::Boolean::Traits<Bool>::True; };
  
}}}} // namespace CShift::LWF::Traits::Match

#endif // CSHIFT_LWF_TRAITS_MATCH_TYPE_H
