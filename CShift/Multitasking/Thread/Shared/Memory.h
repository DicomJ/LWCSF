#ifndef CSHIFT_MULTITASKING_THREAD_SHARED_MEMORY_H
#define CSHIFT_MULTITASKING_THREAD_SHARED_MEMORY_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "Multitasking/Thread.h"
#include "Multitasking/Shared/Memory.h"
#include "Platform/OS/Independent/Multitasking/Thread/Shared/Memory.h"

namespace CShift {
namespace Multitasking {

struct Thread::Shared::Memory
    : Multitasking::Shared::Memory<
      Platform::OS::Independent::Multitasking::Thread::Shared::Memory> {
};

}} // namespace CShift::Multitasking

#endif // CSHIFT_MULTITASKING_THREAD_SHARED_MEMORY_H
