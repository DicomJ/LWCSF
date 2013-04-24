#ifndef CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_H
#define CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include <errno.h>

#include "Platform/OS/API/Thread.h"
#include "LWF/Custom/Allocator.h"
#include "LWF/Null.h"
#include "LWF/Flags.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {

template <typename Memory>struct Thread::Mutex : LWF::Traits::Noncopyable {


  struct Type : LWF::Flags {
    enum {
      Normal      = PTHREAD_MUTEX_NORMAL,
      ErrorCheck  = PTHREAD_MUTEX_ERRORCHECK,
      Recursive   = PTHREAD_MUTEX_RECURSIVE,
      Default     = PTHREAD_MUTEX_DEFAULT
    };
    Type(LWF::Flags::Type type) : LWF::Flags(type) {}
  };

  struct Priority : LWF::Flags {
    enum {
      None      = PTHREAD_PRIO_NONE,
      Inherit   = PTHREAD_PRIO_INHERIT,
      Protected = PTHREAD_PRIO_PROTECT
    };

    Priority(LWF::Flags::Type priority) : LWF::Flags(priority) {}
  };

  struct Attribute;
  struct Condition;

  Bool lock()     { return (Result)pthread_mutex_lock(*this); }
  Bool tryLock()  { return Result::except(pthread_mutex_trylock(*this), EBUSY, False); }
  Bool unlock()   { return (Result)pthread_mutex_unlock(*this); }

  Bool operator == (const Mutex &mutex) const { return this == &mutex; }

  operator const pthread_mutex_t * () const { return &*mutex; }
  operator       pthread_mutex_t * ()       { return &*mutex; }

  Mutex(const Memory &memory, const Attribute &attribute)
    : mutex(memory), initialized(False) {
    if (null == mutex) {
      mutex = new (mutex.allocator()) pthread_mutex_t;
      initialized = (Result)pthread_mutex_init(*this, attribute);
    }
  }
  ~Mutex() {
    if (initialized) {
      (CShift::LWF::Debug::Assert)(Result)pthread_mutex_destroy(*this);
    }
  }

  static const UInt Shared = sizeof(pthread_mutex_t);

  private: typename Memory::template Object<pthread_mutex_t> mutex;
  private: Bool initialized;
};

template <typename Memory>
struct Thread::Mutex<Memory>::Attribute {

  typedef typename Thread::Mutex<Memory>::Mutex Mutex;

  Attribute() : initialized((Result)pthread_mutexattr_init(&attribute)) {}
  ~Attribute() {
    if (initialized) {
      (CShift::LWF::Debug::Assert)(Result)pthread_mutexattr_destroy(&attribute);
    }
  }

  Bool shared() const {
    int pshared = PTHREAD_PROCESS_PRIVATE;
    (Result)pthread_mutexattr_getpshared(*this, &pshared);
    return PTHREAD_PROCESS_SHARED == pshared;
  }

  Attribute &shared(Bool shared) {
    (Result)pthread_mutexattr_setpshared(*this,
      shared ? PTHREAD_PROCESS_SHARED : PTHREAD_PROCESS_PRIVATE);
    return *this;
  }

  Mutex::Type type() const {
    int type = Mutex::Type::Default;
    (Result)pthread_mutexattr_gettype(*this, &type);
    return (Mutex::Type)type;
  }
  Attribute &type(Mutex::Type type) {
    (Result)pthread_mutexattr_settype(*this, type);
    return *this;
  }

  Mutex::Priority protocol() const {
    int priority = Mutex::Priority::None;
    (Result)pthread_mutexattr_getprotocol(*this, &priority);
    return (Mutex::Priority)priority;
  }
  Attribute &protocol(Mutex::Priority priority) {
    (Result)pthread_mutexattr_setprotocol(*this, priority);
    return *this;
  }

  Mutex::Priority ceiling() const {
    int priority = Mutex::Priority::None;
    (Result)pthread_mutexattr_getprioceiling(*this, &priority);
    return (Mutex::Priority)priority;
  }
  Attribute &ceiling(Mutex::Priority priority) {
    (Result)pthread_mutexattr_setprioceiling(*this, priority);
    return *this;
  }

  operator const pthread_mutexattr_t * () const { return &attribute; }
  operator       pthread_mutexattr_t * ()       { return &attribute; }

  private: pthread_mutexattr_t attribute;
  private: Bool initialized;
};

}}}} // namespace CShift::Platform::OS::API

#endif // CSHIFT_PLATFORM_OS_API_THREAD_MUTEX_H
