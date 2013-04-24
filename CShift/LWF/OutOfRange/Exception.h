#ifndef CSHIFT_LWF_OUTOFRANGE_EXCEPTION_H
#define CSHIFT_LWF_OUTOFRANGE_EXCEPTION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Exception.h"

namespace CShift {
namespace LWF {
namespace OutOfRange {

struct Exception : LWF::Exception {
  virtual const Char8 *what() const throw() {
    return "Out of range";
  }
};

}}} // namespace CShift::LWF::OutOfRange

#endif // CSHIFT_LWF_OUTOFRANGE_EXCEPTION_H
