#ifndef CSHIFT_LWF_TRAITS_NONCOPYABLE_H
#define CSHIFT_LWF_TRAITS_NONCOPYABLE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Traits {

class Noncopyable {
  Noncopyable(const Noncopyable &) {}
  Noncopyable &operator = (const Noncopyable &) { return *this; }
  protected: Noncopyable() {}
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_NONCOPYABLE_H
