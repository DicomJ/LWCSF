#ifndef CSHIFT_MULTITASKING_PROCESS_SHARED_MEMORY_H
#define CSHIFT_MULTITASKING_PROCESS_SHARED_MEMORY_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Process.h"
#include "Multitasking/Shared/Memory.h"
#include "Platform/OS/Independent/Multitasking/Process/Shared/Memory.h"

#include "LWF/Reference/Ptr.h"
#include "Text/String.h"

namespace CShift {
namespace Multitasking {

struct Process::Shared::Memory
    : Multitasking::Shared::Memory<
      Platform::OS::Independent::Multitasking::Process::Shared::Memory> {

  static LWF::Reference::Ptr<Memory> create(const Text::String &name, UInt size) {
    return new Process::Shared::Memory(name, size);
  }

  private: Memory(const Text::String &name, UInt size)
    : Multitasking::Shared::Memory<
      Platform::OS::Independent::Multitasking::
      Process::Shared::Memory>(name, size) {}
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_PROCESS_SHARED_MEMORY_H
