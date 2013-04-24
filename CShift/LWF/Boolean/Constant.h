#ifndef CSHIFT_LWF_BOOLEAN_CONSTANT_H
#define CSHIFT_LWF_BOOLEAN_CONSTANT_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {
namespace Boolean {
namespace Constant {

static const Bool False = LWF::Type<Bool>::False;
static const Bool True = LWF::Type<Bool>::True;

}}}} // namespace CShift::LWF::Boolean::Constant
  

namespace CShift {
namespace LWF {
using namespace LWF::Boolean::Constant;
}} // namespace CShift::LWF

namespace CShift {
using namespace LWF::Boolean::Constant;
} // namespace CShift

#endif // CSHIFT_LWF_BOOLEAN_CONSTANT_H
