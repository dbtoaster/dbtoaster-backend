
#ifndef VERSION_H
#define VERSION_H

#include <atomic>
#include "types.h"
template <typename T>
struct EntryMV;

template <typename T>
struct Version {
    T obj;
    timestamp xactid;
    std::atomic<Version*> oldV;

    Version(const Version& that) : obj(that.obj) {
    }

    Version(const T&o) : obj(o) {
    }
    //    template <typename... Args>
    //    Version(bool ignore, const Args&... args): obj(args...), entry(nullptr), xactid(mask), oldV(nullptr){
    //    }
};

template <typename T>
struct EntryMV {
    std::atomic<Version<T>*> versionHead;
    EntryMV<T> *nxt, *prv;

    EntryMV() : versionHead(nullptr), nxt(nullptr), prv(nullptr) {

    }

    EntryMV(Version<T>* v) : versionHead(v), nxt(nullptr), prv(nullptr) {

    }
};
#endif /* VERSION_H */

