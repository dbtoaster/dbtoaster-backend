#ifndef DBTOASTER_UTILS_HPP
#define DBTOASTER_UTILS_HPP

namespace dbtoaster {

namespace utils {

constexpr size_t stringLength(const char* s) {
  return (*s == 0) ? 0 : 1 + stringLength(s + 1);
}

constexpr bool stringEqual(const char* x, const char* y) {
  return (*x == 0 && *y == 0) || (*x == *y && stringEqual(x + 1, y + 1));
}

}

}

#endif /* DBTOASTER_UTILS_HPP */