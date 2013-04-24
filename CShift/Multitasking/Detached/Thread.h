#ifndef CSHIFT_MULTITASKING_DETACHED_THREAD_H
#define CSHIFT_MULTITASKING_DETACHED_THREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Thread.h"

namespace CShift {
namespace Multitasking {
namespace Detached {

struct Thread : CShift::Multitasking::Thread {
  Thread(Runnable &runnbale) { start(runnbale); }
  ~Thread() { detach(); }
};

}}} // namespace CShift::Multitasking::Detached

#endif // CSHIFT_MULTITASKING_DETACHED_THREAD_H
