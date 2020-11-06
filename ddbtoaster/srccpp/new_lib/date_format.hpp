#ifndef DBTOASTER_DATEFORMAT_HPP
#define DBTOASTER_DATEFORMAT_HPP

#include "date_type.hpp"

namespace dbtoaster {

// Expected date format YYYY-MM-DD
struct DateFormat {
  static constexpr DateType parse(const char* str) {
    return DateType(
      parseNumber(str, find('-', str)),
      parseNumber(find('-', str) + 1, find('-', find('-', str) + 1)),
      parseNumber(find('-', find('-', str) + 1) + 1)
    );
  }

 private:
  static constexpr const char* find(char c, const char* str, size_t len) {
    return (len == 0) ? throw "Character not found" :
           ((str[0] == c) ? str : find(c, str + 1, len - 1));
  }

  static constexpr const char* find(char c, const char* str) {
    return find(c, str, strlen(str));
  }

  static constexpr size_t parseDigit(const char* str, size_t i) {
    return (str[i] >= '0' && str[i] <= '9') ?
           static_cast<size_t>(str[i]-'0') :
           throw "Error: digit format";
  }

  static constexpr size_t parseNumber(const char* str, size_t i) {
    return (i == 0) ?
           parseDigit(str, i) :
           parseNumber(str, i - 1) * 10 + parseDigit(str, i);
  }

  static constexpr size_t parseNumber(const char* str) {
    return parseNumber(str, strlen(str) - 1);
  }

  static constexpr size_t parseNumber(const char* start, const char* end) {
    return parseNumber(start, static_cast<size_t>(end - start - 1));
  }
};

}
#endif /* DBTOASTER_DATEFORMAT_HPP */