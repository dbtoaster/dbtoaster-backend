#ifndef DBTOASTER_RINGS_MIN_STRUCT_HPP
#define DBTOASTER_RINGS_MIN_STRUCT_HPP

#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

// SKELETON CLASS - NOT IMPLEMENTED yet

struct MinRing : NumericRing {
  int count;
  DoubleType sum;

  explicit constexpr MinRing() : count(0), sum(0.0) { }

  explicit constexpr MinRing(int c, DoubleType s) : count(c), sum(s) { }

  inline constexpr bool isZero() const { return count == 0; }

  inline constexpr DoubleType result() const {
    return (count != 0 ? sum : 0.0);
  }

  inline MinRing& operator+=(const MinRing& other) {
    this->count += other.count;
    this->sum += other.sum;
    return *this;
  }

  inline constexpr MinRing operator+(const MinRing& other) const {
    return MinRing(count + other.count, sum + other.sum);
  }

  inline constexpr MinRing operator*(const MinRing& other) const {
    return MinRing(count * other.count, sum * other.sum);
  }

};

inline constexpr MinRing operator*(long v, const MinRing& a) {
  return MinRing(v * a.count, v * a.sum);
}

inline constexpr MinRing operator*(const MinRing& a, long v) {
  return MinRing(v * a.count, v * a.sum);
}

}

}

#endif /* DBTOASTER_RINGS_MIN_STRUCT_HPP */