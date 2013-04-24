#ifndef CSHIFT_MULTITASKING_SHARED_MEMORY_H
#define CSHIFT_MULTITASKING_SHARED_MEMORY_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Unique/Ptr.h"
#include "LWF/Destroying/Deleter.h"
#include "LWF/Debug/Assert.h"
#include "Text/String.h"

namespace CShift {
namespace Multitasking {
namespace Shared {

template <typename Base>
struct Memory : Base {

  template <typename T> struct Object;
  Memory() {}
  Memory(const Text::String &name, UInt size) : Base(name, size) {}
};

template <typename Base>
template <typename T>
struct Memory<Base>::Object : LWF::Weak::Ptr<T>  {

  Object(const Memory &memory) : block(memory), deleter(null, Allocator()) {
    if (memory) { LWF::Weak::Ptr<T>::operator = (block); }
  }

  Object &operator = (T * ptr) {
    LWF::Debug::Assert(ptr == (LWF::Weak::Ptr<T>)block && null == *this && null == deleter);
    LWF::Weak::Ptr<T>::operator = (ptr);
    deleter = typename Unique::Ptr(ptr, allocator());
    return *this;
  }

  private: struct Allocator;

  public: Allocator allocator() { return (LWF::Weak::Ptr<T>)block; }

  private: struct Unique {
    typedef Allocator Deallocator;
    typedef LWF::Unique::Ptr<T, LWF::Destroying::Deleter<T, Deallocator> > Ptr;
  };

  private: typename Memory::template Block<T> block;
  private: typename Unique::Ptr deleter;
};

template <typename Base>
template <typename T>
struct Memory<Base>::Object<T>::Allocator {

  Allocator(const LWF::Weak::Ptr<T> &object = null) : object(object)  {}

  Void *allocate(UInt size) const { return
    LWF::Debug::Assert(size == LWF::Type<T>::size), (Void *)&*object;
  }
  Void deallocate(Void *ptr) const {
    LWF::Debug::Assert((T *)ptr == &*object);
  }

  private: LWF::Weak::Ptr<T> object;
};

}}} // namespace CShift::Multitasking::Shared

#endif // CSHIFT_MULTITASKING_SHARED_MEMORY_H
