#ifndef CSHIFT_MULTITASKING_EXCEPTION_SAFE_RUNNABLE_H
#define CSHIFT_MULTITASKING_EXCEPTION_SAFE_RUNNABLE_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Exception.h"
#include "Multitasking/Runnable.h"

namespace CShift {
namespace Multitasking {
namespace Exception {
namespace Safe {

struct Runnable : Multitasking::Runnable {

  Runnable(Multitasking::Runnable &runnable) : runnable(runnable) {}
  /*virtual */Void run() {
    CShift_LWF_Exception_try {
      runnable.run();
    } CShift_LWF_Exception_catch(const LWF::Exception &) {
      // TODO: log out
    } CShift_LWF_Exception_catch(...) {
      // TODO: log out
    }
  }

  private: Multitasking::Runnable &runnable;
};

}}}} // namespace CShift::Multitasking::Extendable

#endif // CSHIFT_MULTITASKING_EXCEPTION_SAFE_RUNNABLE_H
