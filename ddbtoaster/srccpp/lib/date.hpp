#ifndef DBTOASTER_DATE_HPP
#define DBTOASTER_DATE_HPP

namespace dbtoaster {

    struct DateType {
      public:   
        DateType() : day(0), month(0), year(0) { }
        DateType(uint16_t y, uint8_t m, uint8_t d) : day(d), month(m), year(y) { }       

        uint16_t get_year() const { return year; }

        uint8_t get_month() const { return month; }

        uint8_t get_day() const { return day; }

        uint32_t get_numeric() const { return numeric; }

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

#endif /* DBTOASTER_DATE_HPP */
