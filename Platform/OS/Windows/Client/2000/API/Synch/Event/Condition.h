#ifndef CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_CONDITION_H
#define CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_CONDITION_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Platform/OS/API/Synch/Event.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace API {
namespace Synch {

template <typename Mutex_>
class Event::Condition : Event {

  typedef typename Mutex_::Memory Memory;

  struct Traits {
    struct Mutex {
      struct Unlock {
        Unlock(Mutex_ &mutex) : mutex(mutex) { mutex.unlock(); }
        ~Unlock() { mutex.lock(); } private: Mutex_ &mutex;
      };
      struct Lock {
        struct Unlock : Traits::Mutex::Unlock {
          Unlock(Lock &lock) : Traits::Mutex::Unlock(lock.mutex) {}
        };
        Lock(Mutex_ &mutex) : mutex(mutex) { mutex.lock(); }
        ~Lock() { mutex.unlock(); } private: Mutex_ &mutex;
      };
    };

    struct Wait {
      struct Lock : Traits::Mutex::Lock {
        Lock(Condition &condition)
          : Traits::Mutex::Lock(condition.mutex), condition(condition) {
          ++condition.count->wait;
        }
        ~Lock(){
          --condition.count->wait;
          --condition.count->release;
          if (0 == condition.count->wait) { condition.Event::reset(); }
        }
        private: Condition &condition;
      };
      struct Unlock : Traits::Mutex::Lock {
        Unlock(Condition &condition, UInt count = 1)
          : Traits::Mutex::Lock(condition.mutex) {
          if (condition.count->wait != 0) {
            condition.count->release += count;
            condition.Event::set();
          }
        }
      };
    };
  }; // struct Traits
  public:

  Void signal() { typename Traits::Wait::Unlock unlock(*this); }
  Void broadcast() { typename Traits::Wait::Unlock unlock(*this, count->wait); }

  Void wait(Mutex_ &mutex) {
    typename Traits::Wait::Lock lock(*this); {
    typename Traits::Mutex::Lock::Unlock unlock(lock); {
    typename Traits::Mutex::Unlock unlock(mutex);
    Event::wait(); } }
  }

  template <typename Time>
  Bool wait(Mutex_ &mutex, const Time &time) {
    typename Traits::Wait::Lock lock(*this); {
    typename Traits::Mutex::Lock::Unlock unlock(lock); {
    typename Traits::Mutex::Unlock unlock(mutex);
    return Event::wait(time); } }
  }

  Condition(const Memory &memory) : mutex(memory), count(memory) {
    if (null == count) { count = new (count.allocator()) Count(); }
  }

  private: Mutex_ mutex;
  private: struct Count {
    UInt wait; UInt release;
    Count() : wait(0), release(0) {}
  }; typename Memory::template Object<Count> count;

  public: static const UInt Shared = LWF::Type<Count>::size + Mutex_::Shared;
};

}}}}} // namespace CShift::Platform::OS::API::Synch

#endif // CSHIFT_PLATFORM_OS_API_SYNCH_EVENT_CONDITION_H
