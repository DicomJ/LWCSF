#ifndef CSHIFT_LWF_REVERSE_RANGE_H
#define CSHIFT_LWF_REVERSE_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Range.h"
#include "LWF/Reverse/Ptr.h"


namespace CShift {
namespace LWF {
namespace Reverse {

template <typename Iterator>
LWF::Range<LWF::Reverse::Ptr<typename LWF::Traits::Range<Iterator>::Iterator> >
range(const Iterator &begin, const Iterator &end) {
  typedef typename LWF::Traits::Range<Iterator>::Iterator Iterator_;
  return LWF::range(LWF::Reverse::ptr(Iterator_(end)), // Reversing right here!!!
                    LWF::Reverse::ptr(Iterator_(begin)));
}

template <typename Another>
LWF::Range<LWF::Reverse::Ptr<typename Another::Const::Iterator> >
range(const Another &range) {
  return LWF::Reverse::range(range.begin(), range.end());
}

template <typename Another>
LWF::Range<LWF::Reverse::Ptr<typename Another::Iterator> >
range(Another &range) {
  return LWF::Reverse::range(range.begin(), range.end());
}



}}} // namespace CShift::LWF::Reverse

#endif // CSHIFT_LWF_REVERSE_RANGE_H
