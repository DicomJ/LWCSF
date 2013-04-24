#ifndef CSHIFT_MULTITASKING_PROCESS_H
#define CSHIFT_MULTITASKING_PROCESS_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/Multitasking/Process.h"

namespace CShift {
namespace Multitasking {

struct Process : protected Platform::OS::Multitasking::Process {

  private: typedef Platform::OS::Multitasking::Process Base; public:

  struct Shared { struct Memory; };

  struct Mutex; struct Timed { struct Mutex; };
  struct Recursive { struct Mutex; struct Timed { struct Mutex; }; };

  struct RW { struct Mutex; };

  typedef typename Base::Id Id;
  Id id() const { return Base::id(); }

  Bool operator == (const Process &process) const { return id() == process.id(); }
  Bool operator != (const Process &process) const { return !(*this == process); }

  Process() {}
  protected: Process(const typename Base::Self &self) : Base(self) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_H
