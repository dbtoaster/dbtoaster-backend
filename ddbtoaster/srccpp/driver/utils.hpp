#ifndef DRIVER_UTILS_HPP
#define DRIVER_UTILS_HPP

#include <cstdio>
#include <string>
#include <type_traits>
#include "compatibility.hpp"
#include "types.hpp"

template <typename T>
T convert(const std::string&) { throw "Unsupported type conversion"; }

template <>
inline std::string convert<std::string>(const std::string& s) { return s; }

template <>
inline char convert<char>(const std::string& s) { return s[0]; }

template <>
inline int convert<int>(const std::string& s) { return std::stoi(s); }

template <>
inline long convert<long>(const std::string& s) { return std::stol(s); }

template <>
inline unsigned long convert<unsigned long>(const std::string& s) { return std::stoul(s); }

template <>
inline long long convert<long long>(const std::string& s) { return std::stoll(s); }

template <>
inline unsigned long long convert<unsigned long long>(const std::string& s) { return std::stoull(s); }

template <>
inline float convert<float>(const std::string& s) { return std::stof(s); }

template <>
inline double convert<double>(const std::string& s) { return std::stod(s); }

template <>
inline long double convert<long double>(const std::string& s) { return std::stold(s); }

template<>
inline dbtoaster::DateType convert<dbtoaster::DateType>(const std::string& s) {
  return dbtoaster::DateFormat::parse(s.c_str());
}

// Define a type which holds an unsigned integer value
template<size_t> struct int_{};

template <class Tuple>
constexpr void fill_tuple(Tuple& tuple, const std::string& line, char delimiter, size_t start = 0) {
  return fill_tuple(tuple, line, delimiter, start, int_<tuple_size<Tuple>::value>());
}

template <class Tuple, size_t N>
constexpr void fill_tuple(Tuple& tuple, const std::string& line, char delimiter, size_t start, int_<N>) {
  typedef typename tuple_element<tuple_size<Tuple>::value-N, Tuple>::type FieldTp;
  size_t found = line.find(delimiter, start);
  get<tuple_size<Tuple>::value-N>(tuple) = convert<FieldTp>(line.substr(start, found - start));
  fill_tuple(tuple, line, delimiter, found + 1, int_<N-1>());
}

template <class Tuple>
constexpr void fill_tuple(Tuple& tuple, const std::string& line, char delimiter, size_t start, int_<1>) {
  typedef typename tuple_element<tuple_size<Tuple>::value-1, Tuple>::type FieldTp;
  size_t found = line.find(delimiter, start);
  get<tuple_size<Tuple>::value-1>(tuple) = convert<FieldTp>(line.substr(start, found - start));
}

template <class Tuple, class Function, size_t Offset, size_t... Ints>
constexpr void invoke(const Tuple& t, const Function& f, integer_sequence<size_t, Ints...>, int_<Offset>) {
  f(get<Ints + Offset>(t)...);
}

template <class Tuple, class Function, size_t Offset>
constexpr void invoke(const Tuple& t, const Function& f, int_<Offset> o) {
  invoke(t, f, make_index_sequence<tuple_size<Tuple>::value-Offset>{}, o);
}

template <class Tuple, class Function>
constexpr void invoke(const Tuple& t, const Function& f) {
  invoke(t, f, make_index_sequence<tuple_size<Tuple>::value>{}, int_<0>());
}

#endif /* DRIVER_UTILS_HPP */