#ifndef CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_H
#define CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_H

#include "Platform/OS/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Runnable.h"

namespace CShift {
namespace Platform {
namespace OS {
namespace Multitasking {

struct Process {
  struct Mutex;
  struct Recursive { struct Mutex; };

  struct Shared { struct Memory; };

  typedef Int Id;
  Id id() const { return 0; }

  protected: typedef Int Self;
  protected: Self self() { return 0; }
  protected: Process(Self /*self*/) {}

  protected: Process() {}
};

}}}} // namespace CShift::Platform::OS::Multitasking

#endif // CSHIFT_PLATFORM_OS_MULTITASKING_PROCESS_H
