#ifndef DBTOASTER_RINGS_MAX_STRUCT_HPP
#define DBTOASTER_RINGS_MAX_STRUCT_HPP

#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

// SKELETON CLASS - NOT IMPLEMENTED yet

struct MaxRing : NumericRing {
  int count;
  DoubleType sum;

  explicit constexpr MaxRing() : count(0), sum(0.0) { }

  explicit constexpr MaxRing(int c, DoubleType s) : count(c), sum(s) { }

  inline constexpr bool isZero() const { return count == 0; }

  inline constexpr DoubleType result() const {
    return (count != 0 ? sum : 0.0);
  }

  inline MaxRing& operator+=(const MaxRing& other) {
    this->count += other.count;
    this->sum += other.sum;
    return *this;
  }

  inline constexpr MaxRing operator+(const MaxRing& other) const {
    return MaxRing(count + other.count, sum + other.sum);
  }

  inline constexpr MaxRing operator*(const MaxRing& other) const {
    return MaxRing(count * other.count, sum * other.sum);
  }

};

inline constexpr MaxRing operator*(long v, const MaxRing& a) {
  return MaxRing(v * a.count, v * a.sum);
}

inline constexpr MaxRing operator*(const MaxRing& a, long v) {
  return MaxRing(v * a.count, v * a.sum);
}

}

}

#endif /* DBTOASTER_RINGS_MIN_STRUCT_HPP */