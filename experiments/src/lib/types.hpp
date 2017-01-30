#ifndef DBTOASTER_TYPES_HPP
#define DBTOASTER_TYPES_HPP

#include <stdexcept>
#include "string.hpp"

//#define DOUBLE_ZERO_APPROXIMATED
//#define DOUBLE_ZERO_THRESHOLD 1e-8

namespace dbtoaster
{
    typedef long date;

    typedef long DATE_TYPE;

    typedef double DOUBLE_TYPE;

    typedef size_t HASH_RES_t;

    //typedef RefCountedString STRING_TYPE;

    typedef PooledRefCountedString STRING_TYPE;

    //typedef VariableLengthString STRING_TYPE;

    //typedef FixedLengthString<10> STRING_TYPE;

    //typedef std::string STRING_TYPE;
    
    template<typename V>
    struct ZeroValue 
    {
        V get() { return V(); }
        FORCE_INLINE bool isZero(V a) { return (a == V()); }
    };

    template<>
    struct ZeroValue<int> 
    {
        int get() { return 0; }
        FORCE_INLINE bool isZero(int a) { return (a == 0); }
    };

    template<>
    struct ZeroValue<long> 
    {
        long get() { return 0L; }
        FORCE_INLINE bool isZero(long a) { return (a == 0L); }
    };

    template<>
    struct ZeroValue<float> 
    {
        float get() { return 0.0f; }
        FORCE_INLINE bool isZero(float a) { return (a == 0.0f); }
    };

    template<>
    struct ZeroValue<double> 
    {
        double get() { return 0.0; }
    #ifdef DOUBLE_ZERO_APPROXIMATED
        FORCE_INLINE bool isZero(double a) { return (a >= -DOUBLE_ZERO_THRESHOLD && a <= DOUBLE_ZERO_THRESHOLD); }
    #else
        FORCE_INLINE bool isZero(double a) { return (a == 0.0); }
    #endif
    };
}

#endif /* DBTOASTER_TYPES_HPP */