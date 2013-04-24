#ifndef CSHIFT_MULTITASKING_EXTENDABLE_THREAD_H
#define CSHIFT_MULTITASKING_EXTENDABLE_THREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Thread.h"
#include "Multitasking/Exception/Safe/Runnable.h"

namespace CShift {
namespace Multitasking {
namespace Extendable {

struct Thread : CShift::Multitasking::Thread, protected Runnable {

  private: typedef CShift::Multitasking::Thread Base;

  protected: Thread() : started(False), alive(False), safe(*this) {}

  protected: Void start () {
    LWF::Debug::Assert(!started && !alive, "The thread can't be started twice");
    if (!started && !alive) { Base::start(safe); started = alive = True; }
  }
  protected: Void join  () {
    LWF::Debug::Assert(started, "The thread should be started before joining");
    LWF::Debug::Assert(Current::Thread() != *this, "The thread can't be joined by itself");
    if (alive) { Base::join  (); alive = False; }
  }
  private: Void detach();
  protected: ~Thread() {
    LWF::Debug::Assert(!*this, "join() must be called before destroying");
  }

  protected: operator Bool () const { return alive; }

  private: Bool started, alive;
  private: Multitasking::Exception::Safe::Runnable safe;
};

}}} // namespace CShift::Multitasking::Extendable

#endif // THREAD_CSHIFT_MULTITASKING_EXTENDABLE_H
