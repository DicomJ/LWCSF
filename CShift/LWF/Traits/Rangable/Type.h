#ifndef CSHIFT_LWF_TRAITS_RANGABLE_TYPE_H
#define CSHIFT_LWF_TRAITS_RANGABLE_TYPE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type/Declaration.h"
#include "LWF/Traits/Is.Has.h"


namespace CShift {
namespace LWF {
namespace Traits {
namespace Rangable {

template<typename T>
class Type {
  struct Prototype { Void begin() {}; Void end() {}; };
  struct Ambiguous : LWF::Traits::Exclusively::Nonfundamental<T>, Prototype {};
  class Begin {
    template <typename U>
    static LWF::Traits::Isnot criterion(U *,
        LWF::Traits::Match::Value<Void (Prototype::*)(), &U::begin> * = 0);
    static LWF::Traits::Is    criterion(...);
    public: static const Bool is =
            (sizeof(criterion((Ambiguous*)0)) == sizeof(LWF::Traits::Is));
  };
  class End {
    template <typename U>
    static LWF::Traits::Isnot criterion(U *,
         LWF::Traits::Match::Value<Void (Prototype::*)(), &U::end> * = 0);
    static LWF::Traits::Is    criterion(...);
    public: static const Bool is =
            (sizeof(criterion((Ambiguous*)0)) == sizeof(LWF::Traits::Is));
  };
  public: static const Bool range = (Begin::is && End::is);
};

}}}} // namespace CShift::Traits::Rangable

#endif // CSHIFT_LWF_TRAITS_RANGABLE_TYPE_H
