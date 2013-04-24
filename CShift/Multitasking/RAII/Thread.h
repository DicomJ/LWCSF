#ifndef CSHIFT_MULTITASKING_RAII_THREAD_H
#define CSHIFT_MULTITASKING_RAII_THREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Extendable/Thread.h"

namespace CShift {
namespace Multitasking {
namespace RAII {

struct Thread : CShift::Multitasking::Extendable::Thread {

  private: typedef CShift::Multitasking::Extendable::Thread Base; public:

  Thread(Multitasking::Runnable &runnable_)
    : runnable(runnable_) { Base::start(); }

  private: /*virtual */Void run() { runnable.run(); }
  public: ~Thread() { LWF::Debug::Assert(*this); Base::join(); }

  private: Runnable &runnable;
};

}}} // namespace CShift::Multitasking::RAII

#endif // CSHIFT_MULTITASKING_RAII_THREAD_H
