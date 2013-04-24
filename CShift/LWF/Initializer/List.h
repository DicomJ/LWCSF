#ifndef CSHIFT_LWF_INITIALIZER_LIST_H
#define CSHIFT_LWF_INITIALIZER_LIST_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#if PLATFORM_COMPILER_INITIALIZER_LIST

#include <initializer_list>
#include "LWF/Forward/reference.h"


namespace CShift {
namespace LWF {
namespace Initializer {


template <typename T>
struct List: std::initializer_list<T> {
  typedef std::initializer_list<T> Base;

  typedef T Type;
  typedef typename Base::iterator Iterator;

  #if 0
    List(Base &&list) : Base(LWF::Forward::reference<Base>(list)) {}
  #else
    List(const Base &list) : Base(list) {}
  #endif // C++11
};

}}} // namespace CShift::LWF::Initializer

#endif //C++11

#endif // CSHIFT_LWF_INITIALIZER_LIST_H
