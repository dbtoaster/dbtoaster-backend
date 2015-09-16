#ifndef DBTOASTER_HASH_HPP
#define DBTOASTER_HASH_HPP

#include "macro.hpp"

namespace dbtoaster 
{
    uint32_t MurmurHash2(const void* key, int len, uint32_t seed);

    template <class T>
    FORCE_INLINE void hash_combine(size_t& seed, const T& v)
    {
        seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <>
    FORCE_INLINE void hash_combine(size_t& seed, const long& v)
    {
        seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <>
    FORCE_INLINE void hash_combine(size_t& seed, const double& v)
    {
        seed ^= (size_t)(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<size_t SZ>
    FORCE_INLINE void hash_combine(size_t& seed, const FixedLengthString<SZ>& v)
    {        
        seed ^= MurmurHash2(v.data_, sizeof(char) * (v.size_ - 1), 0) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<>
    FORCE_INLINE void hash_combine(size_t& seed, const VariableLengthString& v)
    {
        seed ^= MurmurHash2(v.data_, sizeof(char) * (v.size_ - 1), 0) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<>
    FORCE_INLINE void hash_combine(size_t& seed, const RefCountedString& v)
    {
        seed ^= MurmurHash2(v.data_, sizeof(char) * (v.size_ - 1), 0) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<>
    FORCE_INLINE void hash_combine(size_t& seed, const PooledRefCountedString& v)
    {
        seed ^= MurmurHash2(v.data_, sizeof(char) * (v.size_ - 1), 0) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<>
    FORCE_INLINE void hash_combine(size_t& seed, const PString& v)
    {
        seed ^= MurmurHash2(v.data_, sizeof(char) * (v.size_ - 1), 0) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }    

    FORCE_INLINE uint32_t MurmurHash2(const void* key, int len, uint32_t seed)
    {
        // 'm' and 'r' are mixing constants generated offline.
        // They're not really 'magic', they just happen to work well.
        const uint32_t m = 0x5bd1e995;
        const int r = 24;

        // Initialize the hash to a 'random' value
        uint32_t h = seed ^ len;

        // Mix 4 bytes at a time into the hash
        const unsigned char* data = (const unsigned char*)key;

        while (len >= 4)
        {
            uint32_t k = *(uint32_t*)data;

            k *= m;
            k ^= k >> r;
            k *= m;

            h *= m;
            h ^= k;

            data += 4;
            len -= 4;
        }

        // Handle the last few bytes of the input array
        switch (len)
        {
            case 3: h ^= data[2] << 16;
            case 2: h ^= data[1] << 8;
            case 1: h ^= data[0];
            h *= m;
        };

        // Do a few final mixes of the hash to ensure the last few
        // bytes are well-incorporated.
        h ^= h >> 13;
        h *= m;
        h ^= h >> 15;

        return h;
    } 
}

#endif /* DBTOASTER_HASH_HPP */