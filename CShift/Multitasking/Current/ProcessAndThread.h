#ifndef CSHIFT_MULTITASKING_CURRENT_PROCESSANDTHREAD_H
#define CSHIFT_MULTITASKING_CURRENT_PROCESSANDTHREAD_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Current/Thread.h"
#include "Multitasking/Current/Process.h"

namespace CShift {
namespace Multitasking {
namespace Current {

struct ProcessAndThread {
  struct Id {
    Id() {}
    Id(const Process::Id &pid, const Thread::Id &tid) : pid(pid), tid(tid) {}
    Id(const Id &id) : pid(id.pid), tid(id.tid) {}
    Id &operator = (const Id &id) { pid = id.pid; tid = id.tid; return *this; }
    Bool operator == (const Id &id) const { return pid == id.pid && tid == id.tid; }

    private: Process::Id pid; Thread::Id tid;
  };

  Id id() { return Id(Current::Process().id(), Current::Thread().id()); }
};

}}} // namespace CShift::Multitasking::Current

#endif // CSHIFT_MULTITASKING_CURRENT_PROCESSANDTHREAD_H
