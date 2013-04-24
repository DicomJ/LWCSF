#ifndef CSHIFT_MULTITASKING_CURRENT_THREAD_H
#define CSHIFT_MULTITASKING_CURRENT_THREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Thread.h"

namespace CShift {
namespace Multitasking {
namespace Current {

struct Thread : CShift::Multitasking::Thread {

  private: typedef CShift::Multitasking::Thread Base; public:
  typedef typename Base::Time Time;

  Thread() : Base(Base::self()) {}

  static Void yield() { Base::yield(); }
  static Void sleep(const Time &time) { Base::sleep(time); }
};

}}} // namespace CShift::Multitasking::Current

#endif // CSHIFT_MULTITASKING_CURRENT_THREAD_H
