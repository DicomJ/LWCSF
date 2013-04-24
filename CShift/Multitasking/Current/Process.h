#ifndef CSHIFT_MULTITASKING_CURRENT_PROCESS_H
#define CSHIFT_MULTITASKING_CURRENT_PROCESS_H

#include "Multitasking/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "Multitasking/Process.h"

namespace CShift {
namespace Multitasking {
namespace Current {

struct Process : CShift::Multitasking::Process {

  private: typedef CShift::Multitasking::Process Base; public:

  Process() : Base(Base::self()) {}
};

}}} // namespace CShift::Multitasking::Current

#endif // CSHIFT_MULTITASKING_CURRENT_PROCESS_H
