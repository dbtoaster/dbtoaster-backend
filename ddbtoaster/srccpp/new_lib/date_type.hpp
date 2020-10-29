#ifndef DBTOASTER_DATETYPE_HPP
#define DBTOASTER_DATETYPE_HPP

#include <cstdint>

namespace dbtoaster {

struct DateType {
 public:
  constexpr DateType(uint16_t t_year, uint8_t t_month, uint8_t t_day)
      : day(t_day), month(t_month), year(t_year) { }

  DateType() : day(0), month(0), year(0) { }

  uint16_t getYear() const { return year; }

  uint8_t getMonth() const { return month; }

  uint8_t getDay() const { return day; }

  uint32_t getNumeric() const { return numeric; }

  friend bool operator==(const DateType& d1, const DateType& d2);
  friend bool operator!=(const DateType& d1, const DateType& d2);
  friend bool operator< (const DateType& d1, const DateType& d2);
  friend bool operator<=(const DateType& d1, const DateType& d2);
  friend bool operator> (const DateType& d1, const DateType& d2);
  friend bool operator>=(const DateType& d1, const DateType& d2);

 private:
  union {
    struct {
      uint8_t day;
      uint8_t month;
      uint16_t year;
    };
    uint32_t numeric;
  };
};

inline bool operator==(const DateType& d1, const DateType& d2) { 
  return d1.numeric == d2.numeric;
}

inline bool operator!=(const DateType& d1, const DateType& d2) {
  return d1.numeric != d2.numeric;
}

inline bool operator< (const DateType& d1, const DateType& d2) {
  return d1.numeric < d2.numeric;
}

inline bool operator<=(const DateType& d1, const DateType& d2) {
  return d1.numeric <= d2.numeric;
}

inline bool operator> (const DateType& d1, const DateType& d2) {
  return d1.numeric > d2.numeric;
}

inline bool operator>=(const DateType& d1, const DateType& d2) {
  return d1.numeric >= d2.numeric;
}

}

#endif /* DBTOASTER_DATETYPE_HPP */
