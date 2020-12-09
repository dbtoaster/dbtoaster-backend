#ifndef DBTOASTER_RINGS_MIN_STRUCT_HPP
#define DBTOASTER_RINGS_MIN_STRUCT_HPP

#include <map>
#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

struct MinRing : NumericRing {

  std::map<DoubleType, long> sorted_map;

  explicit MinRing() { }

  explicit MinRing(DoubleType v) : sorted_map { { v, 1 } } { }

  explicit MinRing(const MinRing& other, long a) {
    if (a == 0L) return;
    for (auto& kv : other.sorted_map) {
      sorted_map[kv.first] = kv.second * a;
    }
  }

  inline bool isZero() const { return sorted_map.empty(); }

  inline DoubleType result() const {
    return (sorted_map.empty() ? 0.0 : sorted_map.begin()->first);
  }

  inline MinRing& operator+=(const MinRing& other) {
    for (auto& kv : other.sorted_map) {
      auto it = sorted_map.find(kv.first);
      if (it == sorted_map.end()) {
        sorted_map[kv.first] = kv.second;
      }
      else {
        it->second += kv.second;
        if (it->second == 0L) sorted_map.erase(it);
      }
    }
    return *this;
  }

};

inline MinRing multiply(MinRing&& r, long a) {
  if (a == 0L) return MinRing();
  if (a == 1L) return std::move(r);
  for (auto& kv : r.sorted_map) {
    kv.second *= a;
  }
  return std::move(r);
}

inline MinRing operator*(long a, MinRing&& r) {
  return multiply(std::forward<MinRing>(r), a);
}

inline MinRing operator*(MinRing&& r, long a) {
  return multiply(std::forward<MinRing>(r), a);
}

inline MinRing operator*(long a, const MinRing& r) {
  return MinRing(r, a);
}

inline MinRing operator*(const MinRing& r, long a) {
  return MinRing(r, a);
}

}

}

#endif /* DBTOASTER_RINGS_MIN_STRUCT_HPP */