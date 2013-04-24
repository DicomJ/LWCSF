#ifndef CSHIFT_LWF_PSEUDORANDOM_H
#define CSHIFT_LWF_PSEUDORANDOM_H

#include "LWF/License"
#include "Author/Andriy.Bulka"

#include "LWF/Type.h"


namespace CShift {
namespace LWF {

struct Pseudorandom {

  static UInt number(UInt Begin, UInt Range) {
    static Pseudorandom random; return random.next(Begin, Range);
  }

  UInt current() { return x >> 16; }
  Int current(UInt Begin, UInt Range) {  return Begin + current() % Range; }
  UInt next() { x = (x * 58321) + 11113; return current(); }
  UInt next(UInt Begin, UInt Range) {  return Begin + next() % Range; }

  Pseudorandom(UInt x_ = 123) : x(x_) {}
  private: UInt x;
};

}} // namespace CShift::LWF

#endif // CSHIFT_LWF_PSEUDORANDOM_H
