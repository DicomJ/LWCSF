#ifndef CSHIFT_MULTITASKING_RUNNABLE_H
#define CSHIFT_MULTITASKING_RUNNABLE_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"

namespace CShift {
namespace Multitasking {

struct Runnable {
  virtual Void run() = 0;
  virtual ~Runnable() {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_RUNNABLE_H
