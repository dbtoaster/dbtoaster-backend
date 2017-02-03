#ifndef DBTOASTER_FUNCTIONS_HPP
#define DBTOASTER_FUNCTIONS_HPP

#include "macro.hpp"
#include <regex.h>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace dbtoaster
{
    // Conversion helpers
    DATE_TYPE str2date(const char* c) 
    { 
        unsigned int y, m, d;
        if (sscanf(c, "%u-%u-%u", &y, &m, &d) < 3 || m > 12 || d > 31)
        {
          throw std::invalid_argument(std::string("invalid date string ") + c);
        }
        return (y % 10000) * 10000 + (m % 100) * 100 + (d % 100);
    }

    DATE_TYPE str2date(const STRING_TYPE& s) 
    {
        return str2date(s.c_str());
    }

    DATE_TYPE Udate(const char* c) 
    {
        return str2date(c);
    }

    DATE_TYPE Udate(const STRING_TYPE& s) 
    {
        return str2date(s.c_str());
    }

    FORCE_INLINE long Ulistmax(long v1,  long v2) { return ((v1 > v2) ? v1 : v2 ); }

    FORCE_INLINE DOUBLE_TYPE Ulistmax(DOUBLE_TYPE v1, long v2) { return ((v1 > v2) ? v1 : v2); }

    FORCE_INLINE DOUBLE_TYPE Udiv(DOUBLE_TYPE x) { return (x != 0.0 ? 1.0 / x : 0.0); }

    FORCE_INLINE long Uyear_part(date d) 
    {
        return (d / 10000) % 10000;
    }

    FORCE_INLINE long Umonth_part(date d) 
    {
        return (d / 100) % 100;
    }

    FORCE_INLINE long Uday_part(date d) 
    { 
        return d % 100;
    }

    FORCE_INLINE int Upreg_match(const regex_t& preg, const STRING_TYPE& s)
    {
        int ret = regexec(&preg, s.c_str(), 0, NULL, 0);
        if (ret == 0) return 1;
        else if (ret == REG_NOMATCH) return 0;
         
        std::cerr << "Error evaluating regular expression." << std::endl;
        exit(-1);
    }

    FORCE_INLINE STRING_TYPE Usubstring(const STRING_TYPE &s, uint32_t start, uint32_t len)
    {
        return s.substr(start, len);
    }
}

#endif /* DBTOASTER_FUNCTIONS_HPP */
