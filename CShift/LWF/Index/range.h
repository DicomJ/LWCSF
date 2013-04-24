#ifndef CSHIFT_LWF_INDEX_RANGE_H
#define CSHIFT_LWF_INDEX_RANGE_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Range.h"
#include "LWF/Index/Ptr.h"


namespace CShift {
namespace LWF {
namespace Index {

template <typename Type>
LWF::Range<LWF::Index::Ptr<Type> > range(const Type &begin, const Type &end) {
  return LWF::range(LWF::Index::ptr(begin), LWF::Index::ptr(end));
}

}}} // namespace CShift::LWF::Index

#endif // CSHIFT_LWF_INDEX_RANGE_H
