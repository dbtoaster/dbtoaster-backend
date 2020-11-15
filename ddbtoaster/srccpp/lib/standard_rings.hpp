#ifndef DBTOASTER_STANDARD_RINGS_HPP
#define DBTOASTER_STANDARD_RINGS_HPP

#include "types.hpp"
#include "rings/sum_ring.hpp"
#include "rings/avg_ring.hpp"
#include "rings/min_ring.hpp"
#include "rings/max_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

inline SumRing USumFn(DoubleType v) {
  return SumRing(1, v);
}

inline AvgRing UAvgFn(DoubleType v) {
  return AvgRing(1, v);
}

inline MinRing UMinFn(DoubleType v) {
  return MinRing(1, v);
}

inline MaxRing UMaxFn(DoubleType v) {
  return MaxRing(1, v);
}

}

}

#endif /* DBTOASTER_STANDARD_RINGS_HPP */