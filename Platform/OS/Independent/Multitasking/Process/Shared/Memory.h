#ifndef CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_PROCESS_SHARED_MEMORY_H
#define CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_PROCESS_SHARED_MEMORY_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Intrusive/Ptr.h"
#include "LWF/Reference/Implementation.h"
#include "LWF/Reference/Ptr.h"
#include "LWF/Debug/Assert.h"
#include "Text/String.h"
#include "FS/File/Mapping/View.h"
#include "LWF/Unique/Ptr.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Independent {
namespace Multitasking {
namespace Process {
namespace Shared {

struct Memory : LWF::Reference::Implementation {

  private: struct Mapping :
      private CShift::FS::File,
      private CShift::FS::File::Mapping,
      private CShift::FS::File::Mapping::View {

    typedef LWF::Unique::Ptr<Mapping> Ptr;

    Mapping(const Text::String &name, UInt size) :
      CShift::FS::File(name),
      CShift::FS::File::Mapping(this->CShift::FS::File::truncate(size)),
      CShift::FS::File::Mapping::View(*this, 0, size) {}

    operator Byte * () const { return (Byte *)(Void *)
      static_cast<const CShift::FS::File::Mapping::View &>(*this);
    }
  };

  public: Memory(const Text::String &name, UInt size)
    : name(name),
      mapping(size != 0 ? new Mapping(name, size): null),
      block(size != 0 ? (Byte *)*mapping : null),
      edge(block + size) {}

  operator Bool() const { return False; } // Tells whether memory is initialized
  operator const Text::String &() const { return name; }

  template <typename T> struct Block {

    Block(const Memory &memory)
      : memory(( const_cast<Memory &>(memory).IncRef(),
                &const_cast<Memory &>(memory)) ),
        block(const_cast<Memory &>(memory).operator ++ <T>()) {}

    operator LWF::Weak::Ptr<T> () const { return block; }

    private: LWF::Reference::Ptr<Memory> memory;
    private: LWF::Weak::Ptr<T> block;
  };

  private: template <typename T>
  T *operator ++ () {
    T *block = (T *)this->block;
    this->block += sizeof(T);// TODO: alignment by machine word
    LWF::Debug::Assert(this->block <= edge);
    return block;
  }

  private: Text::String name;
  private: Mapping::Ptr mapping;
  private: Byte *block;
  private: Byte *edge;
};

}}}}}}} // namespace CShift::Plarform::OS::Independent::Multitasking::Process::Shared

#endif // CSHIFT_PLATFORM_OS_INDEPENDENT_PLARFORM_OS_INDEPENDENT_MULTITASKING_PROCESS_SHARED_MEMORY_H
