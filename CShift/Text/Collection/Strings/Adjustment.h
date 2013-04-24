#ifndef CSHIFT_TEXT_COLLECTION_STRINGS_ADJUSTMENT_H
#define CSHIFT_TEXT_COLLECTION_STRINGS_ADJUSTMENT_H

#include "Text/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Vector.h"
#include "LWF/COW.h"
#include "LWF/SCO.h"
#include "Text/Collection/String.h"


namespace CShift {
namespace Text {
namespace Collection {
namespace Strings {

template <typename Encoding_> struct Adjustment {

  typedef Encoding_ Encoding;
  typedef typename Encoding::Char Char;

  struct Allocator : LWF::Collection::Reversible::Vector::Allocator<Char> {
     UInt expanse(UInt/* capacity*/, UInt/* count*/, UInt /*size*/) const {
       return 0;
     }
  };
  struct COW {
    typedef LWF::Collection::COW::Allocator<Adjustment::Allocator> Allocator;
    typedef LWF::COW<LWF::Vector<Char, Allocator> > Base;
    typedef Text::Collection::String<Encoding, Base> String;
  };
  template <UInt machineWords = 8>
  struct SCO {
    typedef LWF::Vector<Char, Adjustment::Allocator> Base;
    static const UInt size = LWF::SCO<1, Base>::template Can<machineWords>::fit;
    typedef Text::Collection::String<Encoding, LWF::SCO<size, Base> > String;
    struct COW {
      typedef Text::Collection::String<Encoding, LWF::SCO<size, typename Adjustment::COW::Base> > String;
    };
  };

  typedef typename SCO<>::COW::String String;
};

}}}} // namespace CShift::Text::Collection::Strings

#endif // CSHIFT_TEXT_COLLECTION_STRINGS_ADJUSTMENT_H
