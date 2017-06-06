
#ifndef SCEXTRA_H
#define SCEXTRA_H
#include <cinttypes>
#include <cstring>
#include <cctype>
#include "hpds/pstring.hpp"
#include "program_base.hpp"
#include "types.h"
#include "GenericEntry.hpp"
#include "Version.h"
#include "Aggregator.hpp"

using namespace std;
using namespace dbtoaster;
#define EXPAND(x) #x
#define STRINGIFY(x) EXPAND(x)
#define CHECK_STAT(x) cerr << STRINGIFY(x) << " -> "; x.getBucketStats()
#define GET_RUN_STAT(x, f) f << "\"" << STRINGIFY(x) << "\" : ["; x.getSizeStats(f); f << "]";
#define GET_RUN_STAT_P(x, f)\
  f << "\"" << STRINGIFY(x) << "\" : [";\
  partitions[0].x.getSizeStats(f);\
  for(int i=1; i<numThreads;++i) { f << "," ; partitions[i].x.getSizeStats(f); }\
  f << "]";

FORCE_INLINE size_t HASH(int x) {
    return x;
}

FORCE_INLINE size_t HASH(char *x) {
    size_t hash = 7;
    for (int i = 0; i < 10 && x[i]; i++) {
        hash = hash * 31 + x[i];
    }
    return hash;
}

FORCE_INLINE size_t HASH(PString const& str) {
    return HASH(str.data_);
}

int strcmpi(const char* This, const char *That) {
    int i = 0;
    while (true) {
        char c1 = tolower(This[i]);
        char c2 = tolower(That[i]);
        if (!c1)
            return c2 ? -1 : 0;
        else if (!c2)
            return 1;
        else if (c1 == c2) {
            i++;
            continue;
        } else if (c1 < c2)
            return -1;
        else return 1;
    }
}

FORCE_INLINE size_t HASH(const Any& a) {
    switch (a.type) {
        case INT: return a.data.i;
            break;
        case STRING: return HASH(a.data.s);
            break;
        case DOUBLE: return HASH(a.data.d);
            break;
        case DATE: return HASH(a.data.t);
            break;
        default: throw std::logic_error("Hash not defined for AnyType " + std::to_string(a.type));
    }
    return -1;
}
char* IntToStrdate(date);



#endif /* SCEXTRA_H */

