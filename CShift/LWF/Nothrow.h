#ifndef CSHIFT_LWF_NOTHROW_H
#define CSHIFT_LWF_NOTHROW_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include <new>
#include "LWF/Type.h"


namespace CShift {
namespace LWF {

struct Nothrow {
  struct Deallocator;
  struct Allocator;
  struct Array {
    struct Deallocator;
    struct Allocator;
  };
  template <typename T>
  struct Deleter;
} const nothrow = Nothrow(); // Nothrow

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_NOTHROW_H
