#ifndef CSHIFT_LWF_DEBUG_H
#define CSHIFT_LWF_DEBUG_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"

namespace CShift {
namespace LWF {

struct Debug {

  struct Assert;

  static const Bool mode =
    #if BUILD_DEBUG
      True
    #else
      False
    #endif
    ;
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_DEBUG_H
