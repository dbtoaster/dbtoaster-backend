#ifndef GEIDX_HPP
#define GEIDX_HPP
#include "GenericEntry.hpp"

class GenericOps {
public:
    FORCE_INLINE static size_t hash(const GenericEntry& e) {
        return 0;

    }

    FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        return 0;

    }
};

class GenericCmp {
public:
    FORCE_INLINE static size_t hash(const GenericEntry& e) {
        return 0;

    }

    FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        return 0;
    }
};
#endif