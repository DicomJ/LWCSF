#ifndef CSHIFT_LWF_TS_REFERENCE_IMPLEMENTATION_H
#define CSHIFT_LWF_TS_REFERENCE_IMPLEMENTATION_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Reference/Implementation.h"
#include "LWF/TS/Shared/Counter.h"


namespace CShift {
namespace LWF {
namespace TS {
namespace Reference {

struct Implementation :
    LWF::Reference::Traits::Implementation<LWF::TS::Shared::Counter> {};

}}}} // namespace CShift::LWF::TS::Reference

#endif // CSHIFT_LWF_TS_REFERENCE_IMPLEMENTATION_H
