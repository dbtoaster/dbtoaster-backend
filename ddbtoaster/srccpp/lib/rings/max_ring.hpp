#ifndef DBTOASTER_RINGS_MAX_STRUCT_HPP
#define DBTOASTER_RINGS_MAX_STRUCT_HPP

#include <map>
#include "numeric_ring.hpp"

namespace dbtoaster {

namespace standard_rings {

struct MaxRing : NumericRing {

  std::map<DoubleType, long> sorted_map;

  explicit MaxRing() { }

  explicit MaxRing(DoubleType v) : sorted_map { { v, 1 } } { }

  explicit MaxRing(const MaxRing& other, long a) {
    if (a == 0L) return;
    for (auto& kv : other.sorted_map) {
      sorted_map[kv.first] = kv.second * a;
    }
  }

  inline bool isZero() const { return sorted_map.empty(); }

  inline DoubleType result() const {
    return (sorted_map.empty() ? 0.0 : sorted_map.rbegin()->first);
  }

  inline MaxRing& operator+=(const MaxRing& other) {
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

inline MaxRing multiply(MaxRing&& r, long a) {
  if (a == 0L) return MaxRing();
  if (a == 1L) return std::move(r);
  for (auto& kv : r.sorted_map) {
    kv.second *= a;
  }
  return std::move(r);
}

inline MaxRing operator*(long a, MaxRing&& r) {
  return multiply(std::forward<MaxRing>(r), a);
}

inline MaxRing operator*(MaxRing&& r, long a) {
  return multiply(std::forward<MaxRing>(r), a);
}

inline MaxRing operator*(long a, const MaxRing& r) {
  return MaxRing(r, a);
}

inline MaxRing operator*(const MaxRing& r, long a) {
  return MaxRing(r, a);
}

}

}

#endif /* DBTOASTER_RINGS_MIN_STRUCT_HPP */