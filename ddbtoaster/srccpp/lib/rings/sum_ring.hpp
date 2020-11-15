#ifndef DBTOASTER_RINGS_SUM_STRUCT_HPP
#define DBTOASTER_RINGS_SUM_STRUCT_HPP

#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

struct SumRing : NumericRing {
  int count;
  DoubleType sum;

  explicit constexpr SumRing() : count(0), sum(0.0) { }

  explicit constexpr SumRing(int c, DoubleType s) : count(c), sum(s) { }

  inline constexpr bool isZero() const { return count == 0; }

  inline constexpr DoubleType result() const {
    return (count != 0 ? sum : 0.0);
  }

  inline SumRing& operator+=(const SumRing& other) {
    this->count += other.count;
    this->sum += other.sum;
    return *this;
  }

  inline constexpr SumRing operator+(const SumRing& other) const {
    return SumRing(count + other.count, sum + other.sum);
  }

  inline constexpr SumRing operator*(const SumRing& other) const {
    return SumRing(count * other.count, sum * other.sum);
  }

};

inline constexpr SumRing operator*(long v, const SumRing& a) {
  return SumRing(v * a.count, v * a.sum);
}

inline constexpr SumRing operator*(const SumRing& a, long v) {
  return SumRing(v * a.count, v * a.sum);
}

}

}

#endif /* DBTOASTER_RINGS_SUM_STRUCT_HPP */