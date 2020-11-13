#ifndef DBTOASTER_DATE_HPP
#define DBTOASTER_DATE_HPP

namespace dbtoaster {

    struct DateType {
      public:   
        DateType() : day(0), month(0), year(0) { }
        DateType(uint16_t y, uint8_t m, uint8_t d) : day(d), month(m), year(y) { }       

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

#endif /* DBTOASTER_DATE_HPP */
