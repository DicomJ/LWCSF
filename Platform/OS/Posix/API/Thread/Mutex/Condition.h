#ifndef CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_CONDITION_H
#define CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "Platform/OS/API/Thread/Mutex.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

template <typename Memory>
struct Thread::Mutex<Memory>::Condition : CShift::LWF::Traits::Noncopyable {

  typedef Thread::Time Time;

  struct Attribute;

  Bool broadcast() { return (Result)pthread_cond_broadcast(*this); }
  Bool signal() { return (Result)pthread_cond_signal(*this); }

  Bool wait(Mutex &mutex) { return (Result)pthread_cond_wait(*this, mutex); }
  Bool wait(Mutex &mutex, const Time &time) {
    return Result::except(pthread_cond_timedwait(*this, mutex, time),
                          ETIMEDOUT, False);
  }

  operator const pthread_cond_t * () const { return &*condition; }
  operator       pthread_cond_t * ()       { return &*condition; }

  Condition(const Memory &memory, const Attribute &attribute)
    : condition(memory), initialized(False) {
    if (null == condition) {
      condition = new (condition.allocator()) pthread_cond_t;
      initialized = (Result)pthread_cond_init(*this, attribute);
    }
  }
  ~Condition() { if (initialized) {
      (CShift::LWF::Debug::Assert)(Result)pthread_cond_destroy(*this);
    }
  }

  static const UInt Shared = sizeof(pthread_cond_t);

  private: typename Memory::template Object<pthread_cond_t> condition;
  private: Bool initialized;
};

template <typename Memory>
struct Thread::Mutex<Memory>::Condition::Attribute {

  Attribute() : initialized((Result)pthread_condattr_init(&attribute)) {}
  ~Attribute() {
    if (initialized) {
      (CShift::LWF::Debug::Assert)(Result)pthread_condattr_destroy(&attribute);
    }
  }

  Bool shared() const {
    int pshared = PTHREAD_PROCESS_PRIVATE;
    (Result)pthread_condattr_getpshared(*this, &pshared);
    return PTHREAD_PROCESS_SHARED == pshared;
  }
  Attribute &shared(Bool shared) {
    (Result)pthread_condattr_setpshared(*this,
      shared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE);
    return *this;
  }

  operator const pthread_condattr_t * () const { return &attribute; }
  operator       pthread_condattr_t * ()       { return &attribute; }

  private: pthread_condattr_t attribute;
  private: Bool initialized;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_CONDITION_H
