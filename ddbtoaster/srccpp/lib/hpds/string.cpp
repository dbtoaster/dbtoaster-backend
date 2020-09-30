#include "string.hpp"
#include "../mmap/pool.hpp"

namespace dbtoaster {

    ValuePool<uint64_t> pool;


    template <uint64_t SIZE>
    std::ostream& operator<<(std::ostream& os, const FixedLengthString<SIZE>& s) {
        os << s.c_str();
        return os;
    }    

    std::ostream& operator<<(std::ostream& os, const VariableLengthString& s) {
        os << s.c_str();
        return os;
    }    

    std::ostream& operator<<(std::ostream& os, const RefCountedString& s) {
        os << s.c_str();
        return os;
    }    

    std::ostream& operator<<(std::ostream& os, const PooledRefCountedString& s) {
        os << s.c_str();
        return os;
    }

}
