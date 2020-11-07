#ifndef DBTOASTER_TYPES_HPP
#define DBTOASTER_TYPES_HPP

#include <string>
#include <type_traits>
#include "date_type.hpp"
#include "map_type.hpp"

namespace dbtoaster {

typedef DateType date;

typedef double DOUBLE_TYPE;

typedef std::size_t HASH_RES_t;

typedef std::string STRING_TYPE;

template<std::size_t Size>
using CStringMap = Map<const char*, const char*, Size>;

template<class T, class Enable = void>
struct Value {
  static constexpr T zero = T();
  static constexpr bool isZero(const T& a) { return a.isZero(); }
};

template<class T, class Enable>
constexpr T Value<T, Enable>::zero;

template <class T>
struct Value<T, typename std::enable_if<std::is_integral<T>::value>::type> {
  static constexpr T zero = 0;
  static constexpr bool isZero(const T& a) { return a == 0; }  
};

template <class T>
constexpr T Value<T, typename std::enable_if<std::is_integral<T>::value>::type>::zero;

template <class T>
struct Value<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
  static constexpr T zero = 0.0;
  static constexpr bool isZero(const T& a) { return a == 0.0; }
};

template <class T>
constexpr T Value<T, typename std::enable_if<std::is_floating_point<T>::value>::type>::zero;

}
#endif /* DBTOASTER_TYPES_HPP */