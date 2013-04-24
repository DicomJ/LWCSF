#ifndef CSHIFT_PLATFORM_OS_API_THREAD_H
#define CSHIFT_PLATFORM_OS_API_THREAD_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include "LWF/Type.h"
#include "LWF/Traits/Noncopyable.h"
#include "LWF/Debug/Assert.h"
#include "Platform/OS/API/Clock/Time.h"
#include "Platform/OS/API/Result.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

struct Thread : CShift::LWF::Traits::Noncopyable {

  template <typename Memory> struct Mutex;

  typedef Platform::OS::API::Clock::Time Time;
  struct Attribute;
  typedef pthread_t Self;
  typedef Void * (*Routine)(Void *);

  struct Id {
    Id() {}
    Id(Self id) : id(id) {}

    Id(const Id &id) : id(id.id) {}
    Id &operator = (const Id &id) { this->id = id.id; return *this; }

    Bool operator == (const Id &id) const {
      return pthread_equal(this->id, id.id);
    }
    Bool operator != (const Id &id) const { return !(*this == id); }

    private: Self id;
  };

  Id id() const { return tid; }

  struct Max { static Int priority() { return sched_get_priority_max(sched_getscheduler(getpid())); } };
  struct Min { static Int priority() { return sched_get_priority_max(sched_getscheduler(getpid())); } };

  Int priority() const {
    sched_param param; int policy;
    (Result)pthread_getschedparam(tid, &policy, &param);
    return param.__sched_priority;
  }

  Void priority(Int priority) {
    sched_param param; param.__sched_priority = priority;
    (Result)pthread_setschedparam(tid, sched_getscheduler(getpid()), &param);
  }

  static Void yield() { (Result)sched_yield(); }
  static Void sleep(const Time &/*time*/) { usleep(0/*TODO: add conversion of the time*/); }


  inline Bool create(Routine routine, Void *parameter, const Attribute &attribute);
  Void join() { (Result)pthread_join(tid, NULL); }
  Void detach() { /*(Result)*/pthread_detach(tid); }

  Thread() {}
  static Self self() { return pthread_self(); }
  Thread(Self tid) : tid(tid) {}

  private: operator Self () const { return tid; }

  private: Self tid;
};

struct Thread::Attribute {

  Attribute() : initialized((Result)pthread_attr_init(&attribute)) {}
  ~Attribute() {
    if (initialized) {
      (CShift::LWF::Debug::Assert)(Result)pthread_attr_destroy(&attribute);
    }
  }

  Bool joinable() const {
    int detachstate = -1;
    (Result)pthread_attr_getdetachstate(*this, &detachstate);
    return PTHREAD_CREATE_JOINABLE == detachstate;
  }

  Attribute &joinable(Bool joinable) {
    (Result)pthread_attr_setdetachstate(*this,
      joinable ? PTHREAD_CREATE_JOINABLE: PTHREAD_CREATE_DETACHED);
    return *this;
  }

  Bool detached() const { return !joinable(); }
  Attribute &detached(Bool detached) { return joinable(!detached); }

  operator const pthread_attr_t * () const { return &attribute; }
  operator       pthread_attr_t * ()       { return &attribute; }
  private: pthread_attr_t attribute;
  private: Bool initialized;
};

inline Bool Thread::create(Routine routine,
                           Void *parameter,
                           const Attribute &attribute) {
  return (Result)pthread_create(&tid, attribute, routine, parameter);
}

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_THREAD_H
