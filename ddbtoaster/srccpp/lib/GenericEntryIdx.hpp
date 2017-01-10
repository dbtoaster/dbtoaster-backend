#ifndef GEIDX_HPP
#define GEIDX_HPP
#include "GenericEntry.hpp"
extern size_t HASH(const Any& a);
class GenericOps {
public:

    FORCE_INLINE static size_t hash(const GenericEntry& e) {
        size_t h = 16;
        for(auto it : e.map){
            h = h * 41 + HASH(it.second);
        }
        return h;
    }
    
    FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        if (e1.isSampleEntry) {
            for (auto it : e1.map) {
                if (e2.map.at(it.first) != it.second)
                    return 1;
            }

        } else if (e2.isSampleEntry) {
            for (auto it : e2.map) {
                if (e1.map.at(it.first) != it.second)
                    return 1;
            }
        }else { //TODO: SBJ: Fix: Assumes that all columns except the last form key
            for(uint i = 1; i < e1.map.size(); ++i){
                if(e1.map.at(i) != e2.map.at(i))
                    return 1;
            }
        }
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