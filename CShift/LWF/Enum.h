#ifndef CSHIFT_LWF_ENUM_H
#define CSHIFT_LWF_ENUM_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Traits/Enum.h"
#include "LWF/Type.h"

namespace CShift {
namespace LWF {

struct Enum : LWF::Traits::Enum<Int32> {
  private: typedef LWF::Traits::Enum<Int32> Base; public:
  Enum(typename Base::Type value) : Base(value) {}
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ENUM_H
