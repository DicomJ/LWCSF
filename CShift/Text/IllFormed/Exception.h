#ifndef CSHIFT_TEXT_ILLFORMED_EXCEPTION_H
#define CSHIFT_TEXT_ILLFORMED_EXCEPTION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Exception.h"

namespace CShift {
namespace Text {
namespace IllFormed {

struct Exception : LWF::Exception {
  virtual const Char8 *what() const throw() {
    return "Ill formed";
  }
};

}}} // namespace CShift::Text::IllFormed

#endif // CSHIFT_TEXT_ILLFORMED_EXCEPTION_H
