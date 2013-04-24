#ifndef CSHIFT_BINARY_STREAM_H
#define CSHIFT_BINARY_STREAM_H

#include "Binary/License"
#include "Author/Andriy.Bulka"

#include "IOF/Stream.h"

namespace CShift {
namespace Binary {

struct Stream : virtual IOF::Stream<Byte> {};

}} // namespace CShift::Binary

#endif // CSHIFT_BINARY_STREAM_H
