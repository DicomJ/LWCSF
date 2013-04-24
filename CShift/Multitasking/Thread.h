#ifndef CSHIFT_MULTITASKING_THREAD_H
#define CSHIFT_MULTITASKING_THREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/Multitasking/Thread.h"

namespace CShift {
namespace Multitasking {

struct Thread : protected Platform::OS::Multitasking::Thread {

  private: typedef Platform::OS::Multitasking::Thread Base; public:

  struct Shared { struct Memory; };

  struct Mutex; struct Timed { struct Mutex; };
  struct Recursive { struct Mutex; struct Timed { struct Mutex; }; };

  struct RW { struct Mutex; };

  typedef typename Base::Id Id;
  Id id() const { return Base::id(); }

  Bool operator == (const Thread &thread) const { return id() == thread.id(); }
  Bool operator != (const Thread &thread) const { return !(*this == thread); }

  struct Max { static Int priority() { return Base::Max::priority(); } };
  struct Min { static Int priority() { return Base::Min::priority(); } };
  Int priority() const { return Base::priority(); }
  Void priority(Int priority) { Base::priority(priority); }

  Thread() {}
  protected: Thread(const typename Base::Self &self) : Base(self) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_H
