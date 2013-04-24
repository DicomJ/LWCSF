#ifndef CSHIFT_LWF_DEREFERENCE_RANGE_H
#define CSHIFT_LWF_DEREFERENCE_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Range.h"
#include "LWF/Dereference/Ptr.h"


namespace CShift {
namespace LWF {
namespace Dereference {

template <typename Iterator>
LWF::Range<LWF::Dereference::Ptr<typename LWF::Weak::Cast<Iterator>::Ptr> >
range(const Iterator &begin, const Iterator &end) {
  typedef typename LWF::Weak::Cast<Iterator>::Ptr Iterator_;
  return LWF::range(LWF::Dereference::ptr(Iterator_(begin)),
                    LWF::Dereference::ptr(Iterator_(end)));
}

template <typename Another>
LWF::Range<LWF::Dereference::Ptr<typename Another::Const::Iterator> >
range(const Another &range) {
  return LWF::Dereference::range(range.begin(), range.end());
}

template <typename Another>
LWF::Range<LWF::Dereference::Ptr<typename Another::Iterator> >
range(Another &range) {
  return LWF::Dereference::range(range.begin(), range.end());
}

}}} // namespace CShift::LWF::Dereference

#endif // CSHIFT_LWF_DEREFERENCE_RANGE_H
