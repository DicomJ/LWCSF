#ifndef CSHIFT_LWF_HASHER_H
#define CSHIFT_LWF_HASHER_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"
#include "LWF/Boolean/Constant.h"


namespace CShift {
namespace LWF {

template <typename Key>
struct Hasher {
  typedef UInt Type;
  static const Bool cache = False;
  Type operator()(const Key &key) const { return Type(key); }
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_HASHER_H
