#ifndef CSHIFT_LWF_TRAITS_ENUM_H
#define CSHIFT_LWF_TRAITS_ENUM_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

namespace CShift {
namespace LWF {
namespace Traits {

template <typename T>
struct Enum {
  typedef T Type;

  Enum(Type value) : value(value) {}

  operator Type() const { return value; }

  private: Type value;
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_ENUM_H
