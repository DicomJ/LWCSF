#ifndef CSHIFT_MULTITASKING_RW_MUTEX_H
#define CSHIFT_MULTITASKING_RW_MUTEX_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Recursive/Timed/Mutex.h"
#include "Multitasking/Recursive/Mutex.h"
#include "Multitasking/Timed/Mutex.h"
#include "Multitasking/Mutex.h"
#include "Multitasking/Synch/Timed/Mutex.h"

namespace CShift {
namespace Multitasking {
namespace RW {

template <typename RWSynch, typename RState, typename WState>
struct Mutex {

  protected: typedef typename RWSynch::Memory Memory;

  private: struct Proxy {

    struct Memory {
      Memory(Mutex &mutex,
             const typename Mutex::Memory &memory)
        : mutex(mutex), memory(memory) {}
      operator Mutex & () const { return mutex; }
      operator const typename Mutex::Memory & () const { return memory; }
      private: Mutex &mutex;
      private: const typename Mutex::Memory &memory;
    };

    struct Synch {
      typedef typename RWSynch::Mutex Mutex;
      typedef typename Mutex::Condition Condition;
      typedef typename Mutex::Lock Lock;
      typedef typename Proxy::Memory Memory;

      static const UInt Shared = 0;

      operator typename RWSynch::Mutex & () { return mutex.synch; }
      operator Condition & () { return mutex.synch; }

      Synch(const typename Proxy::Memory &memory) : mutex(memory) {}
      private: RW::Mutex<RWSynch, RState, WState> &mutex;
    };

    struct Read { struct State : RState {
      State &operator = (Bool unlock) {
        RState::operator = (unlock); return *this;
      }
      operator Bool () const { return !mutex.write; }
      State(const typename Proxy::Memory &memory)
        : RState(memory), mutex(memory) {}
      private: Mutex &mutex;
    };};

    struct Write { struct State : WState {
      State &operator = (Bool unlock) {
        WState::operator = (unlock); return *this;
      }
      operator Bool () const { return  !mutex.write && !mutex.read; }
      State(const typename Proxy::Memory &memory)
        : WState(memory), mutex(memory) {}
      private: Mutex &mutex;
    };};
  };  public:

  typedef Multitasking::Recursive::Timed::Mutex<
          Multitasking::Recursive::Mutex<
          Multitasking::Synch::Timed::Mutex<
            typename Proxy::Synch, typename Proxy::Read::State > > > Read;

  struct Write :  Multitasking::Timed::Mutex<
                  Multitasking::Mutex<
                  Multitasking::Synch::Timed::Mutex<
                   typename Proxy::Synch, typename Proxy::Write::State > > > {
    private: typedef
      Multitasking::Timed::Mutex<
      Multitasking::Mutex<
      Multitasking::Synch::Timed::Mutex<
        typename Proxy::Synch, typename Proxy::Write::State > > > Base; public:
    Write(const typename Base::Memory &memory) : Base(memory) {}
    private: struct Condition;
    private: struct Synch;
  };

  operator Read  & () { return read;  }
  operator Write & () { return write; }

  Mutex(const Memory &memory) :
    synch(typename Proxy::Memory(*this, memory)),
    read (typename Proxy::Memory(*this, memory)),
    write(typename Proxy::Memory(*this, memory)) {}

  private: RWSynch synch;
  private: struct Read_ : Read {
    Read_(const typename Proxy::Memory &memory) : Read(memory) {}
    operator Bool () const { return static_cast<const RState &>(this->state); }
  } read;

  private: struct Write_: Write {
    Write_(const typename Proxy::Memory &memory) : Write(memory) {}
    operator Bool () const { return static_cast<const WState &>(this->state); }
  } write;

  public: static const UInt Shared = RWSynch::Shared +
                                     Read::Shared + Write::Shared;
};

}}} // namespace CShift::Multitasking::RW

#endif // CSHIFT_MULTITASKING_RW_MUTEX_H
