#ifndef CSHIFT_LWF_CONST_RANGE_H
#define CSHIFT_LWF_CONST_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Range.h"
#include "LWF/Const/Ptr.h"


namespace CShift {
namespace LWF {
namespace Const {

template <typename Iterator>
LWF::Range<LWF::Const::Ptr<typename LWF::Traits::Range<Iterator>::Iterator> >
range(const Iterator &begin, const Iterator &end) {
  typedef typename LWF::Traits::Range<Iterator>::Iterator Iterator_;
  return LWF::range(LWF::Const::ptr(Iterator_(begin)),
                    LWF::Const::ptr(Iterator_(end)));
}

template <typename Another>
LWF::Range<LWF::Const::Ptr<typename Another::Const::Iterator> >
range(const Another &range) {
  return LWF::Const::range(range.begin(), range.end());
}

template <typename Another>
LWF::Range<LWF::Const::Ptr<typename Another::Iterator> >
range(Another &range) {
  return LWF::Const::range(range.begin(), range.end());
}

}}} // namespace CShift::LWF::Const

#endif // CSHIFT_LWF_CONST_RANGE_H
