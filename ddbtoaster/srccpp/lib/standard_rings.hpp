#ifndef DBTOASTER_STANDARD_RINGS_HPP
#define DBTOASTER_STANDARD_RINGS_HPP

#include "types.hpp"
#include "rings/sum_ring.hpp"
#include "rings/avg_ring.hpp"
#include "rings/min_ring.hpp"
#include "rings/max_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

inline constexpr SumRing USumFn(DoubleType v) {
  return SumRing(1, v);
}

inline constexpr AvgRing UAvgFn(DoubleType v) {
  return AvgRing(1, v);
}

inline MinRing UMinFn(DoubleType v) {
  return MinRing(v);
}

inline MaxRing UMaxFn(DoubleType v) {
  return MaxRing(v);
}

}

}

#endif /* DBTOASTER_STANDARD_RINGS_HPP */