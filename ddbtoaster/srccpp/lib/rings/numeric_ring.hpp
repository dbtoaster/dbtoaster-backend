#ifndef DBTOASTER_RINGS_NUMERIC_STRUCT_HPP
#define DBTOASTER_RINGS_NUMERIC_STRUCT_HPP

#include "types.hpp"

namespace dbtoaster {

namespace standard_rings {

struct NumericRing { };

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr DoubleType Ucast_as_value(const T& a) {
  return a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator==(const T& a, DoubleType v) {
  return a.result() == v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator==(DoubleType v, const T& a) {
  return v == a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator!=(const T& a, DoubleType v) {
  return a.result() != v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator!=(DoubleType v, const T& a) {
  return v != a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator< (const T& a, DoubleType v) {
  return a.result() < v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator< (DoubleType v, const T& a) {
  return v < a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator<=(const T& a, DoubleType v) {
  return a.result() <= v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator<=(DoubleType v, const T& a) {
  return v <= a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator> (const T& a, DoubleType v) {
  return a.result() > v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator> (DoubleType v, const T& a) {
  return v > a.result();
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator>=(const T& a, DoubleType v) {
  return a.result() >= v;
}

template <class T, typename std::enable_if<std::is_base_of<NumericRing, T>::value>::type* = nullptr>
inline constexpr bool operator>=(DoubleType v, const T& a) {
  return v >= a.result();
}

}

}

#endif /* DBTOASTER_RINGS_NUMERIC_STRUCT_HPP */