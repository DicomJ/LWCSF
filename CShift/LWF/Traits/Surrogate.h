#ifndef CSHIFT_LWF_TRAITS_SURROGATE_H
#define CSHIFT_LWF_TRAITS_SURROGATE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"

namespace CShift {
namespace LWF {
namespace Traits {

template <typename T>
struct Surrogate {

  #if 1 // TODO make it a GCC specific and provide implementation for another compilers
    typedef T __attribute__((__may_alias__)) * Alias;
  #else
    typedef T * Alias;
  #endif

  T &operator * () {
    Alias alias = (Alias)reinterpret_cast<T *>(surrogate);
    return *alias;
  }
  const T &operator * () const {
    const Alias alias = (const Alias)reinterpret_cast<const T *>(surrogate);
    return *alias;
  }

  private: Byte surrogate[sizeof(T)]; // surrogation
};

}}} // namespace CShift::LWF::Traits

#endif // CSHIFT_LWF_TRAITS_SURROGATE_H 
