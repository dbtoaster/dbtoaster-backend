#ifndef DBTOASTER_RINGS_AVG_STRUCT_HPP
#define DBTOASTER_RINGS_AVG_STRUCT_HPP

#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

struct AvgRing : NumericRing {
  int count;
  DoubleType sum;

  explicit constexpr AvgRing() : count(0), sum(0.0) { }

  explicit constexpr AvgRing(int c, DoubleType s) : count(c), sum(s) { }

  inline constexpr bool isZero() const { return count == 0; }

  inline constexpr DoubleType result() const {
    return (count != 0 ? sum / count : 0.0);
  }

  inline AvgRing& operator+=(const AvgRing& other) {
    this->count += other.count;
    this->sum += other.sum;
    return *this;
  }

  inline constexpr AvgRing operator+(const AvgRing& other) const {
    return AvgRing(count + other.count, sum + other.sum);
  }

  inline constexpr AvgRing operator*(const AvgRing& other) const {
    return AvgRing(count * other.count, sum * other.sum);
  }

};

inline constexpr AvgRing operator*(long v, const AvgRing& a) {
  return AvgRing(v * a.count, v * a.sum);
}

inline constexpr AvgRing operator*(const AvgRing& a, long v) {
  return AvgRing(v * a.count, v * a.sum);
}

}

}

#endif /* DBTOASTER_RINGS_AVG_STRUCT_HPP */