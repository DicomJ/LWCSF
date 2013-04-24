#ifndef CSHIFT_LWF_ENDIAN_H
#define CSHIFT_LWF_ENDIAN_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Enum.h"

namespace CShift {
namespace LWF {

struct Endian : LWF::Enum {
  enum { Little, Big };
  Endian(LWF::Enum::Type endian) : LWF::Enum(endian) {}
};

static const Endian::Type endian =
// TODO: determine endian by PLATFORM_HARDWARE_ENDIAN_LITTLE
    Endian::Little;

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_ENDIAN_H
