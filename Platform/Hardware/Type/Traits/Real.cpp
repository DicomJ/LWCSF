#include "Platform/License"
#include "Author/Andriy.Bulka"
#include "Platform/Hardware/Type/Traits/Real.h"


namespace Platform {
namespace Hardware {
namespace Type {

namespace Kind {

template<>
const Type::Real::Float Real::Traits<Type::Real::Float>::max = 3.402823466e+38F;
template<>
const Type::Real::Float Real::Traits<Type::Real::Float>::min = 1.17549435e-38F;

} // namespace Kind

namespace Kind {

template<>
const Type::Real::Double Real::Traits<Type::Real::Double>::max = 1.7976931348623157e+308;
template<>
const Type::Real::Double Real::Traits<Type::Real::Double>::min = 2.2250738585072014e-308;

} // namespace Kind

namespace Kind {

template<>
const Type::Real::LDouble Real::Traits<Type::Real::LDouble>::max = 1.7976931348623157e+308L;
template<>
const Type::Real::LDouble Real::Traits<Type::Real::LDouble>::min = 2.2250738585072014e-308L;

} // namespace Kind

}}} // namespace Platform::Hardware::Type
