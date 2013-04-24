#ifndef CSHIFT_LWF_TS_SHARED_COUNTER_H
#define CSHIFT_LWF_TS_SHARED_COUNTER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace TS {
namespace Shared {

struct Counter {
  Counter(UInt counter) { this->counter = counter; }
  UInt operator ++() { return ++counter; }
  UInt operator --() { return --counter; }
  Bool operator == (UInt counter) const { return counter == this->counter; }
  private: UInt counter;
};

}}}} // namespace CShift::LWF::TS::Shared

#endif // CSHIFT_LWF_TS_SHARED_COUNTER_H
